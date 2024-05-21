
#include <stdio.h>
#include "MK64F12.h"
#include "fsl_clock.h"
#include "FlexTimer.h"


#define MCG_IRCLK_DISABLE 0U                   /*!< MCGIRCLK disabled */
#define MCG_PLL_DISABLE 0U                     /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 0U                           /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE 0U                  /*!< Disable external reference clock */
#define SIM_CLKOUT_SEL_FLEXBUS_CLK 0U          /*!< CLKOUT pin clock select: FlexBus clock */
#define SIM_ENET_1588T_CLK_SEL_OSCERCLK_CLK 2U /*!< SDHC clock select: OSCERCLK clock */
#define SIM_ENET_RMII_CLK_SEL_EXTAL_CLK 0U     /*!< SDHC clock select: Core/system clock */
#define SIM_OSC32KSEL_RTC32KCLK_CLK 2U         /*!< OSC32KSEL select: RTC32KCLK clock (32.768kHz) */
#define SIM_PLLFLLSEL_IRC48MCLK_CLK 3U         /*!< PLLFLL select: IRC48MCLK clock */
#define SIM_PLLFLLSEL_MCGPLLCLK_CLK 1U         /*!< PLLFLL select: MCGPLLCLK clock */
#define SIM_SDHC_CLK_SEL_OSCERCLK_CLK 2U       /*!< SDHC clock select: OSCERCLK clock */
#define SIM_TRACE_CLK_SEL_CORE_SYSTEM_CLK 1U   /*!< Trace clock select: Core/system clock */
#define SIM_USB_CLK_120000000HZ 120000000U     /*!< Input SIM frequency for USB: 120000000Hz */

int main(void) {

	 mcg_pll_config_t 	 pll0Config =
	 	        {
	 	            .enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
	 	            .prdiv      = 0xeU,            /* PLL Reference divider: divided by 15 */
	 	            .vdiv       = 0xCU,            /* VCO divider: multiplied by 36 */
	 	        };


	const osc_config_t osc_config = {
	    .freq        = 50000000U,    /* Oscillator frequency: 50000000Hz */
	    .capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
	    .workMode    = kOSC_ModeExt, /* Use external clock */
	    .oscerConfig = {
	        .enableMode =
	            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
	    }};


	 CLOCK_SetSimSafeDivs();

	 CLOCK_InitOsc0(&osc_config);

	 CLOCK_SetXtal0Freq(osc_config.freq);

	 CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL);
	 CLOCK_SetFbeMode(0, kMCG_Dmx32Default, kMCG_DrsLow, NULL);
	 CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &pll0Config);
	 CLOCK_SetPeeMode();


	SystemCoreClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);

	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
	FlexTimer_Init();

    while(1) {

    }
    return 0 ;
}
