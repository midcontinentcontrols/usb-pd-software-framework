/*******************************************************************************
  PD Generic Timer source file
 
  Company:
    Microchip Technology Inc.
 
  File Name:
    pd_timer.c

  Description:
    This file contains the function definitions that make up the 
    interface to the Power delivery modules.
*******************************************************************************/
/*******************************************************************************
Copyright © [2022] Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software and
any derivatives exclusively with Microchip products. It is your responsibility
to comply with third party license terms applicable to your use of third party
software (including open source software) that may accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES
OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN
ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST
EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU
HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
#include <psf_stdinc.h>
#include <zephyr/kernel.h>

typedef struct pd_timer_data {
    struct k_work work;
    struct k_timer timer;
    uint8_t timer_id;
} pd_timer_data_t;

static pd_timer_data_t _pd_timer_data[MAX_CONCURRENT_TIMERS];

static void pd_timer_workq_handler(struct k_work* work) {
    pd_timer_data_t* data = CONTAINER_OF(work, pd_timer_data_t, work);
    
    // Setting the timer state as "Timer Expired"
    gasPDTimers[data->timer_id].u8TimerStPortNum &= ~PDTIMER_STATE;
    gasPDTimers[data->timer_id].u8TimerStPortNum |= PDTIMER_EXPIRED;
#if MCHP_PSF_CONFIG_16BIT_PDTIMER_COUNTER
    gasPDTimers[data->timer_id].u16TimeoutTickCnt = 0;
#else
    gasPDTimers[data->timer_id].u32TimeoutTickCnt = 0;
#endif
    
    printk("timer %u fired\n", data->timer_id);

    if(gasPDTimers[data->timer_id].pfnTimerCallback == NULL) return;

    // Execute callback OUTSIDE of IRQ context
    gasPDTimers[data->timer_id].pfnTimerCallback(
        gasPDTimers[data->timer_id].u8TimerStPortNum & PDTIMER_PORT_NUM, 
        gasPDTimers[data->timer_id].u8PDState
    );

}

static void pd_timer_expiry_handler(struct k_timer* timer) {
    pd_timer_data_t* data = CONTAINER_OF(timer, pd_timer_data_t, timer);
    k_work_submit(&data->work);
}

/*******************************************************************************/
UINT8 PDTimer_Init() {
	// Setting all the PD Software timer's state to Non Active during PD stack initialization
	for (UINT8 u8TimerID = SET_TO_ZERO; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++) {
		gasPDTimers[u8TimerID].u8TimerStPortNum = RESET_TO_ZERO;
        printk("init timer %u", u8TimerID);
        _pd_timer_data[u8TimerID].timer_id = u8TimerID;
        k_timer_init(&_pd_timer_data[u8TimerID].timer, pd_timer_expiry_handler, NULL);
        k_work_init(&_pd_timer_data[u8TimerID].work, pd_timer_workq_handler);
	}
    
	return TRUE;
}
/*******************************************************************************/

UINT8 PDTimer_Start(UINT32 u32TimeoutTicks, PDTimerCallback pfnTimerCallback, UINT8 u8PortNum, UINT8 u8PDState) {
	UINT8 u8TimerID;
    
    // u32TimeoutTicks is incremented by 1 to make sure guaranteed timer wait is provided
    u32TimeoutTicks++;
    
    // Find the unused PD Software timer and start the given timeout value with the found timer
	for (u8TimerID = SET_TO_ZERO; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++) {
		if  (((gasPDTimers[u8TimerID].u8TimerStPortNum & PDTIMER_STATE) == PDTIMER_NON_ACTIVE) ||
             ((gasPDTimers[u8TimerID].u8TimerStPortNum & PDTIMER_STATE) == PDTIMER_EXPIRED))
		{
#if (TRUE == MCHP_PSF_CONFIG_16BIT_PDTIMER_COUNTER)
                gasPDTimers[u8TimerID].u16TimeoutTickCnt = (UINT16)u32TimeoutTicks;
#else
                gasPDTimers[u8TimerID].u32TimeoutTickCnt = u32TimeoutTicks;
#endif

            //Store the callback function address and arguments to be passed in the PD Software timer structure
			gasPDTimers[u8TimerID].pfnTimerCallback = pfnTimerCallback;
			gasPDTimers[u8TimerID].u8TimerStPortNum = (u8PortNum & PDTIMER_PORT_NUM);
			gasPDTimers[u8TimerID].u8PDState = u8PDState;
            
            //Setting the PD Software timer state to "Active"
			gasPDTimers[u8TimerID].u8TimerStPortNum &= ~PDTIMER_STATE;
            gasPDTimers[u8TimerID].u8TimerStPortNum |= PDTIMER_ACTIVE;
            printk("PD start timer %u for %lu ms\n", u8TimerID, u32TimeoutTicks);
            k_timer_start(&_pd_timer_data[u8TimerID].timer, K_MSEC(u32TimeoutTicks), K_NO_WAIT);
            break;
		}
	}
	return u8TimerID;
}
/**************************************************************************************/

/**************************************************************************************/
void PDTimer_Kill(UINT8 u8TimerID) {
    MCHP_PSF_HOOK_DISABLE_GLOBAL_INTERRUPT();

    if (u8TimerID < MAX_CONCURRENT_TIMERS) {       
        //Setting the PD Software timer to "Non Active"
        gasPDTimers[u8TimerID].u8TimerStPortNum &= ~PDTIMER_STATE;
        gasPDTimers[u8TimerID].pfnTimerCallback = NULL;
        k_timer_stop(&_pd_timer_data[u8TimerID].timer);
    }

    MCHP_PSF_HOOK_ENABLE_GLOBAL_INTERRUPT();
}
/**************************************************************************************/
void PDTimer_KillPortTimers(UINT8 u8PortNum) {
    MCHP_PSF_HOOK_DISABLE_GLOBAL_INTERRUPT();

    // Resetting all the module's TimerID globals
	gasPolicyEngine[u8PortNum].u8PETimerID = MAX_CONCURRENT_TIMERS;
	gasTypeCcontrol[u8PortNum].u8TypeCTimerID = MAX_CONCURRENT_TIMERS;
    #if (TRUE == INCLUDE_PD_3_0)
	gasChunkSM [u8PortNum].u8CAorChunkSMTimerID = MAX_CONCURRENT_TIMERS;
    #endif
	gasPolicyEngine[u8PortNum].u8PENoResponseTimerID = MAX_CONCURRENT_TIMERS;
    
	#if (TRUE == INCLUDE_POWER_FAULT_HANDLING)
	gasDPM[u8PortNum].u8VBUSPowerGoodTmrID = MAX_CONCURRENT_TIMERS;
    gasDPM[u8PortNum].u8VCONNPowerGoodTmrID = MAX_CONCURRENT_TIMERS;
	#endif
    
    #if (TRUE == INCLUDE_PD_SOURCE_PPS)
    gasDPM[u8PortNum].u8PPSFaultPersistTmrID = MAX_CONCURRENT_TIMERS;
    #endif

    #if (TRUE == INCLUDE_PD_VCONN_SWAP)
    gasDPM[u8PortNum].u8VCONNSwapWaitTmrID = MAX_CONCURRENT_TIMERS;
    gasDPM[u8PortNum].u8DiscoverIdentityTmrID = MAX_CONCURRENT_TIMERS;
    #endif /*INCLUDE_PD_VCONN_SWAP*/

    #if (TRUE == INCLUDE_PD_PR_SWAP)
    gasDPM[u8PortNum].u8PRSwapWaitTmrID = MAX_CONCURRENT_TIMERS;
    #endif 
    
    #if (TRUE == INCLUDE_PD_DR_SWAP)
    gasDPM[u8PortNum].u8DRSwapWaitTmrID = MAX_CONCURRENT_TIMERS;
    #endif

    #if (TRUE == INCLUDE_PD_VDM)
    gasDPM[u8PortNum].u8VDMBusyTmrID = MAX_CONCURRENT_TIMERS;
    #endif 
    
    #if (TRUE == INCLUDE_PD_ALT_MODE)
    gasDPM[u8PortNum].u8AMETmrID = MAX_CONCURRENT_TIMERS;
    #endif 

    //Setting the PD Software timers of a given port number to "Non Active"
    for (UINT8 u8TimerID = SET_TO_ZERO; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++) {
        if  (((gasPDTimers[u8TimerID].u8TimerStPortNum & PDTIMER_STATE) == PDTIMER_ACTIVE) &&
             ((gasPDTimers[u8TimerID].u8TimerStPortNum & PDTIMER_PORT_NUM) == u8PortNum)
#if (TRUE == INCLUDE_POWER_MANAGEMENT_CTRL)
			// If power management is active don't kill IDLE Timer
            && (u8TimerID != gau8PortIdleTimerID[u8PortNum])
#endif
            )
        {
            // Setting the Timer state to inactive
            gasPDTimers[u8TimerID].u8TimerStPortNum &= ~PDTIMER_STATE;
            gasPDTimers[u8TimerID].pfnTimerCallback = NULL;
            k_timer_stop(&_pd_timer_data[u8TimerID].timer);
        }
    }
	
    MCHP_PSF_HOOK_ENABLE_GLOBAL_INTERRUPT();
}
/**************************************************************************************/

/**************************************************************************************/
    
 
    