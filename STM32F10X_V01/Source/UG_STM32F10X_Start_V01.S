;===============================================================================================================================
UG_Stack_Size   EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
UG_Stack_Mem    SPACE   UG_Stack_Size
__UG_initial_sp

UG_Heap_Size    EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__UG_heap_base
UG_Heap_Mem     SPACE   UG_Heap_Size
__UG_heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    UG_RESET, DATA, READONLY
                EXPORT  __UG_Vectors
                EXPORT  __UG_Vectors_End
                EXPORT  __UG_Vectors_Size

__UG_Vectors    DCD     __UG_initial_sp               ; Top of Stack
                DCD     UG_Reset_Handler              ; Reset Handler
                DCD     UG_NMI_Handler                ; NMI Handler
                DCD     UG_HardFault_Handler          ; Hard Fault Handler
                DCD     UG_MemManage_Handler          ; MPU Fault Handler
                DCD     UG_BusFault_Handler           ; Bus Fault Handler
                DCD     UG_UsageFault_Handler         ; Usage Fault Handler
                DCD     UG_RSVD_N9_Handler            ; Reserved
                DCD     UG_RSVD_N8_Handler            ; Reserved
                DCD     UG_RSVD_N7_Handler            ; Reserved
                DCD     UG_RSVD_N6_Handler            ; Reserved
                DCD     UG_SVC_Handler                ; SVCall Handler
                DCD     UG_DebugMon_Handler           ; Debug Monitor Handler
                DCD     UG_RSVD_N3_Handler            ; Reserved
                DCD     UG_PendSV_Handler             ; PendSV Handler
                DCD     UG_SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     UG_WWDG_IRQHandler            ; Window Watchdog
                DCD     UG_PVD_IRQHandler             ; PVD through EXTI Line detect
                DCD     UG_TAMPER_IRQHandler          ; Tamper
                DCD     UG_RTC_IRQHandler             ; RTC
                DCD     UG_FLASH_IRQHandler           ; Flash
                DCD     UG_RCC_IRQHandler             ; RCC
                DCD     UG_EXTI0_IRQHandler           ; EXTI Line 0
                DCD     UG_EXTI1_IRQHandler           ; EXTI Line 1
                DCD     UG_EXTI2_IRQHandler           ; EXTI Line 2
                DCD     UG_EXTI3_IRQHandler           ; EXTI Line 3
                DCD     UG_EXTI4_IRQHandler           ; EXTI Line 4
                DCD     UG_DMA1_Channel1_IRQHandler   ; DMA1 Channel 1
                DCD     UG_DMA1_Channel2_IRQHandler   ; DMA1 Channel 2
                DCD     UG_DMA1_Channel3_IRQHandler   ; DMA1 Channel 3
                DCD     UG_DMA1_Channel4_IRQHandler   ; DMA1 Channel 4
                DCD     UG_DMA1_Channel5_IRQHandler   ; DMA1 Channel 5
                DCD     UG_DMA1_Channel6_IRQHandler   ; DMA1 Channel 6
                DCD     UG_DMA1_Channel7_IRQHandler   ; DMA1 Channel 7
                DCD     UG_ADC12_IRQHandler           ; ADC12
                DCD     UG_USB1HP_CAN1TX_IRQHandler   ; USB High Priority or CAN1 TX
                DCD     UG_USB1LP_CAN1RX0_IRQHandler  ; USB Low  Priority or CAN1 RX0
                DCD     UG_CAN1RX1_IRQHandler         ; CAN1 RX1
                DCD     UG_CAN1SCE_IRQHandler         ; CAN1 SCE
                DCD     UG_EXTI9_5_IRQHandler         ; EXTI Line 9..5
                DCD     UG_TIM1_BRK_IRQHandler        ; TIM1 Break
                DCD     UG_TIM1_UP_IRQHandler         ; TIM1 Update
                DCD     UG_TIM1_TRGCOM_IRQHandler     ; TIM1 Trigger and Commutation
                DCD     UG_TIM1_CC_IRQHandler         ; TIM1 Capture Compare
                DCD     UG_TIM2_IRQHandler            ; TIM2
                DCD     UG_TIM3_IRQHandler            ; TIM3
                DCD     UG_TIM4_IRQHandler            ; TIM4
                DCD     UG_I2C1_EV_IRQHandler         ; I2C1 Event
                DCD     UG_I2C1_ER_IRQHandler         ; I2C1 Error
                DCD     UG_I2C2_EV_IRQHandler         ; I2C2 Event
                DCD     UG_I2C2_ER_IRQHandler         ; I2C2 Error
                DCD     UG_SPI1_IRQHandler            ; SPI1
                DCD     UG_SPI2_IRQHandler            ; SPI2
                DCD     UG_USART1_IRQHandler          ; USART1
                DCD     UG_USART2_IRQHandler          ; USART2
                DCD     UG_USART3_IRQHandler          ; USART3
                DCD     UG_EXTI15_10_IRQHandler       ; EXTI Line 15..10
                DCD     UG_RTCAlarm_IRQHandler        ; RTC Alarm through EXTI Line
                DCD     UG_USBWakeUp_IRQHandler       ; USB Wakeup from suspend
				        DCD     0
                DCD     0					
				        DCD     UG_USB2HP_IRQHandler	       ;can use with can
                DCD     UG_USB2LP_IRQHandler	       ;can use with can						
__UG_Vectors_End

__UG_Vectors_Size  EQU  __UG_Vectors_End - __UG_Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
UG_Reset_Handler    PROC
                 EXPORT  UG_Reset_Handler             [WEAK]
                 IMPORT  __main
                 LDR     R0, =__main
                 BX      R0
                 ENDP

UGMain           PROC
                 EXPORT  UGMain                       [WEAK]
                 IMPORT  UG_main
                 LDR     R0, = UG_main
                 BX      R0
                 ENDP
; Dummy Exception Handlers (infinite loops which can be modified)

UG_NMI_Handler     PROC
                EXPORT  UG_NMI_Handler                [WEAK]
                B       .
                ENDP
UG_HardFault_Handler\
                PROC
                EXPORT  UG_HardFault_Handler          [WEAK]
                B       .
                ENDP
UG_MemManage_Handler\
                PROC
                EXPORT  UG_MemManage_Handler          [WEAK]
                B       .
                ENDP
UG_BusFault_Handler\
                PROC
                EXPORT  UG_BusFault_Handler           [WEAK]
                B       .
                ENDP
UG_UsageFault_Handler\
                PROC
                EXPORT  UG_UsageFault_Handler         [WEAK]
                B       .
                ENDP
UG_RSVD_N9_Handler\
                PROC
                EXPORT  UG_RSVD_N9_Handler            [WEAK]
                B       .
                ENDP
UG_RSVD_N8_Handler\
                PROC
                EXPORT  UG_RSVD_N8_Handler            [WEAK]
                B       .
                ENDP
UG_RSVD_N7_Handler\
                PROC
                EXPORT  UG_RSVD_N7_Handler            [WEAK]
                B       .
                ENDP
UG_RSVD_N6_Handler\
                PROC
                EXPORT  UG_RSVD_N6_Handler            [WEAK]
                B       .
                ENDP
UG_SVC_Handler     PROC
                EXPORT  UG_SVC_Handler                [WEAK]
                B       .
                ENDP
UG_DebugMon_Handler\
                PROC
                EXPORT  UG_DebugMon_Handler           [WEAK]
                B       .
                ENDP
UG_RSVD_N3_Handler\
                PROC
                EXPORT  UG_RSVD_N3_Handler            [WEAK]
                B       .
                ENDP
UG_PendSV_Handler  PROC
                EXPORT  UG_PendSV_Handler             [WEAK]
                B       .
                ENDP
UG_SysTick_Handler PROC
                EXPORT  UG_SysTick_Handler            [WEAK]
                B       .
                ENDP

UG_Default_Handler PROC

                EXPORT  UG_WWDG_IRQHandler            [WEAK]
                EXPORT  UG_PVD_IRQHandler             [WEAK]
                EXPORT  UG_TAMPER_IRQHandler          [WEAK]
                EXPORT  UG_RTC_IRQHandler             [WEAK]
                EXPORT  UG_FLASH_IRQHandler           [WEAK]
                EXPORT  UG_RCC_IRQHandler             [WEAK]
                EXPORT  UG_EXTI0_IRQHandler           [WEAK]
                EXPORT  UG_EXTI1_IRQHandler           [WEAK]
                EXPORT  UG_EXTI2_IRQHandler           [WEAK]
                EXPORT  UG_EXTI3_IRQHandler           [WEAK]
                EXPORT  UG_EXTI4_IRQHandler           [WEAK]
                EXPORT  UG_DMA1_Channel1_IRQHandler   [WEAK]
                EXPORT  UG_DMA1_Channel2_IRQHandler   [WEAK]
                EXPORT  UG_DMA1_Channel3_IRQHandler   [WEAK]
                EXPORT  UG_DMA1_Channel4_IRQHandler   [WEAK]
                EXPORT  UG_DMA1_Channel5_IRQHandler   [WEAK]
                EXPORT  UG_DMA1_Channel6_IRQHandler   [WEAK]
                EXPORT  UG_DMA1_Channel7_IRQHandler   [WEAK]
                EXPORT  UG_ADC12_IRQHandler           [WEAK]
                EXPORT  UG_USB1HP_CAN1TX_IRQHandler   [WEAK]
                EXPORT  UG_USB1LP_CAN1RX0_IRQHandler  [WEAK]
                EXPORT  UG_CAN1RX1_IRQHandler         [WEAK]
                EXPORT  UG_CAN1SCE_IRQHandler         [WEAK]
                EXPORT  UG_EXTI9_5_IRQHandler         [WEAK]
                EXPORT  UG_TIM1_BRK_IRQHandler        [WEAK]
                EXPORT  UG_TIM1_UP_IRQHandler         [WEAK]
                EXPORT  UG_TIM1_TRGCOM_IRQHandler     [WEAK]
                EXPORT  UG_TIM1_CC_IRQHandler         [WEAK]
                EXPORT  UG_TIM2_IRQHandler            [WEAK]
                EXPORT  UG_TIM3_IRQHandler            [WEAK]
                EXPORT  UG_TIM4_IRQHandler            [WEAK]
                EXPORT  UG_I2C1_EV_IRQHandler         [WEAK]
                EXPORT  UG_I2C1_ER_IRQHandler         [WEAK]
                EXPORT  UG_I2C2_EV_IRQHandler         [WEAK]
                EXPORT  UG_I2C2_ER_IRQHandler         [WEAK]
                EXPORT  UG_SPI1_IRQHandler            [WEAK]
                EXPORT  UG_SPI2_IRQHandler            [WEAK]
                EXPORT  UG_USART1_IRQHandler          [WEAK]
                EXPORT  UG_USART2_IRQHandler          [WEAK]
                EXPORT  UG_USART3_IRQHandler          [WEAK]
                EXPORT  UG_EXTI15_10_IRQHandler       [WEAK]
                EXPORT  UG_RTCAlarm_IRQHandler        [WEAK]
                EXPORT  UG_USBWakeUp_IRQHandler       [WEAK]
                EXPORT  UG_USB2HP_IRQHandler          [WEAK]
                EXPORT  UG_USB2LP_IRQHandler          [WEAK]
UG_WWDG_IRQHandler
UG_PVD_IRQHandler
UG_TAMPER_IRQHandler
UG_RTC_IRQHandler
UG_FLASH_IRQHandler
UG_RCC_IRQHandler
UG_EXTI0_IRQHandler
UG_EXTI1_IRQHandler
UG_EXTI2_IRQHandler
UG_EXTI3_IRQHandler
UG_EXTI4_IRQHandler
UG_DMA1_Channel1_IRQHandler
UG_DMA1_Channel2_IRQHandler
UG_DMA1_Channel3_IRQHandler
UG_DMA1_Channel4_IRQHandler
UG_DMA1_Channel5_IRQHandler
UG_DMA1_Channel6_IRQHandler
UG_DMA1_Channel7_IRQHandler
UG_ADC12_IRQHandler
UG_USB1HP_CAN1TX_IRQHandler
UG_USB1LP_CAN1RX0_IRQHandler
UG_CAN1RX1_IRQHandler
UG_CAN1SCE_IRQHandler
UG_EXTI9_5_IRQHandler
UG_TIM1_BRK_IRQHandler
UG_TIM1_UP_IRQHandler
UG_TIM1_TRGCOM_IRQHandler
UG_TIM1_CC_IRQHandler
UG_TIM2_IRQHandler
UG_TIM3_IRQHandler
UG_TIM4_IRQHandler
UG_I2C1_EV_IRQHandler
UG_I2C1_ER_IRQHandler
UG_I2C2_EV_IRQHandler
UG_I2C2_ER_IRQHandler
UG_SPI1_IRQHandler
UG_SPI2_IRQHandler
UG_USART1_IRQHandler
UG_USART2_IRQHandler
UG_USART3_IRQHandler
UG_EXTI15_10_IRQHandler
UG_RTCAlarm_IRQHandler
UG_USBWakeUp_IRQHandler
UG_USB2HP_IRQHandler
UG_USB2LP_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB           
                
                 EXPORT  __UG_initial_sp
                 EXPORT  __UG_heap_base
                 EXPORT  __UG_heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __UG_user_initial_stackheap
                 
__UG_user_initial_stackheap

                 LDR     R0, =  UG_Heap_Mem
                 LDR     R1, =(UG_Stack_Mem + UG_Stack_Size)
                 LDR     R2, = (UG_Heap_Mem +  UG_Heap_Size)
                 LDR     R3, = UG_Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF
;===============================================================================================================================
			           END
;===============================================================================================================================
