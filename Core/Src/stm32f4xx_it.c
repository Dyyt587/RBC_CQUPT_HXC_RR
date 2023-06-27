/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
 #include "bsp_sbus.h"
 
 //ȫ����λ����  ����6
#define BUFFERSIZE 255	//�ɽ��յ����������
extern uint8_t Rx_len_Huart7;//����6���ճ���
extern uint8_t ReceiveBuff_Huart7[BUFFERSIZE]; //����6���ջ�����
extern int testcount;
extern float pos_x;//����X--ZBx
extern float pos_y;//����Y--ZBy
extern float zangle;//�����
extern float xangle;//������
extern float yangle;//�����
extern float w_z;//�������

extern float set_pos_x;
extern float set_pos_y;
extern float set_zangle;
extern int move_flag;

//������ ����2
extern uint8_t Rx_len_Huart2;//����2���ճ���
extern uint8_t ReceiveBuff_Huart2[BUFFERSIZE]; //����2���ջ�����
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart7_rx;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;
extern TIM_HandleTypeDef htim14;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles CAN1 TX interrupts.
  */
void CAN1_TX_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_TX_IRQn 0 */

  /* USER CODE END CAN1_TX_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_TX_IRQn 1 */

  /* USER CODE END CAN1_TX_IRQn 1 */
}

/**
  * @brief This function handles CAN1 RX0 interrupts.
  */
void CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */

  /* USER CODE END CAN1_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
  uart_receive_handler(&huart1);
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	uint32_t temp;//���㴮�ڽ��յ������ݸ���
    int re[4] = {0};
    if(USART2 == huart2.Instance)//�ж��Ƿ�Ϊ����1�ж�
    {
        if(RESET != __HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE))//���Ϊ����1����
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart2);//����жϱ�־
            HAL_UART_DMAStop(&huart2);//ֹͣDMA����
            temp  = __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);//��ȡDMA��ǰ���ж���δ���
            Rx_len_Huart2 =  BUFFERSIZE - temp; //���㴮�ڽ��յ������ݸ���
            /*************************************************************************/
            //�������ݴ���
						//ͷ55��aaβ��0d��0A��һ��22����
            if(ReceiveBuff_Huart2[0]==0x55&&ReceiveBuff_Huart2[1]==0xAA&&ReceiveBuff_Huart2[20]==0x0D&&ReceiveBuff_Huart2[21]==0x0A)
            {
                //��������
                if(ReceiveBuff_Huart2[2]==0x01)
                {
                    re[0] = ReceiveBuff_Huart2[7]  << 24 | ReceiveBuff_Huart2[6]  << 16 | ReceiveBuff_Huart2[5]  << 8 | ReceiveBuff_Huart2[4];
                    re[1] = ReceiveBuff_Huart2[11] << 24 | ReceiveBuff_Huart2[10] << 16 | ReceiveBuff_Huart2[9]  << 8 | ReceiveBuff_Huart2[8];
                    re[2] = ReceiveBuff_Huart2[15] << 24 | ReceiveBuff_Huart2[14] << 16 | ReceiveBuff_Huart2[13] << 8 | ReceiveBuff_Huart2[12];
                    re[3] = ReceiveBuff_Huart2[19] << 24 | ReceiveBuff_Huart2[18] << 16 | ReceiveBuff_Huart2[17] << 8 | ReceiveBuff_Huart2[16];
                    set_pos_y=re[0];
                    set_pos_x=re[1];
                    set_zangle=re[2];
                    move_flag=re[3];
                    printf("Y=%d    X=%d    yaw=%d  flag=%d\r\n", (int)set_pos_y,(int) set_pos_x, (int)set_zangle, move_flag);
                    Usart2Printf("n20.val=%d\xff\xff\xff",(int)set_pos_y);
                    Usart2Printf("n21.val=%d\xff\xff\xff",(int)set_pos_x);
                    Usart2Printf("n22.val=%d\xff\xff\xff",(int)set_zangle);
                    Usart2Printf("n26.val=%d\xff\xff\xff",move_flag);
                }
            }
            /*************************************************************************/
            //���¿�����һ�ν���
            //memset(ReceiveBuff_Huart2,0,sizeof(ReceiveBuff_Huart2));
            Rx_len_Huart2=0;//�������ݳ�������
            HAL_UART_Receive_DMA(&huart2,ReceiveBuff_Huart2,BUFFERSIZE);//������һ�ν���
        }
    }
  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream1 global interrupt.
  */
void DMA2_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream1_IRQn 0 */

  /* USER CODE END DMA2_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart6_rx);
  /* USER CODE BEGIN DMA2_Stream1_IRQn 1 */

  /* USER CODE END DMA2_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles CAN2 TX interrupts.
  */
void CAN2_TX_IRQHandler(void)
{
  /* USER CODE BEGIN CAN2_TX_IRQn 0 */

  /* USER CODE END CAN2_TX_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan2);
  /* USER CODE BEGIN CAN2_TX_IRQn 1 */

  /* USER CODE END CAN2_TX_IRQn 1 */
}

/**
  * @brief This function handles CAN2 RX0 interrupts.
  */
void CAN2_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN2_RX0_IRQn 0 */

  /* USER CODE END CAN2_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan2);
  /* USER CODE BEGIN CAN2_RX0_IRQn 1 */

  /* USER CODE END CAN2_RX0_IRQn 1 */
}

/**
  * @brief This function handles USART6 global interrupt.
  */
void USART6_IRQHandler(void)
{
  /* USER CODE BEGIN USART6_IRQn 0 */

  /* USER CODE END USART6_IRQn 0 */
  HAL_UART_IRQHandler(&huart6);
  /* USER CODE BEGIN USART6_IRQn 1 */
	
  /* USER CODE END USART6_IRQn 1 */
}

/**
  * @brief This function handles UART7 global interrupt.
  */
void UART7_IRQHandler(void)
{
  /* USER CODE BEGIN UART7_IRQn 0 */

  /* USER CODE END UART7_IRQn 0 */
  HAL_UART_IRQHandler(&huart7);
  /* USER CODE BEGIN UART7_IRQn 1 */
	uint32_t temp;//���㴮�ڽ��յ������ݸ���
    static union
    {
        uint8_t date[24];
        float ActVal[6];
    } posture;
    if(UART7 == huart7.Instance)//�ж��Ƿ�Ϊ����1�ж�
    {
        if(RESET != __HAL_UART_GET_FLAG(&huart7,UART_FLAG_IDLE))//���Ϊ����1����
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart7);//����жϱ�־
            HAL_UART_DMAStop(&huart7);//ֹͣDMA����
            temp  = __HAL_DMA_GET_COUNTER(&hdma_usart7_rx);//��ȡDMA��ǰ���ж���δ���
            Rx_len_Huart7 =  BUFFERSIZE - temp; //���㴮�ڽ��յ������ݸ���
            /*************************************************************************/
            //�������ݴ���
            if(Rx_len_Huart7==28)
            {
                for(int i=0; i<24; i++)
                {
                    posture.date[i]=ReceiveBuff_Huart7[i+2];
                }
                zangle=-posture.ActVal[0];
                xangle=posture.ActVal[1];
                yangle=posture.ActVal[2];
                pos_x=posture.ActVal[3];
                pos_y=posture.ActVal[4];
                w_z=posture.ActVal[5];
            }
            /*************************************************************************/
            //���¿�����һ�ν���
            Rx_len_Huart7=0;//�������ݳ�������
            HAL_UART_Receive_DMA(&huart7,ReceiveBuff_Huart7,BUFFERSIZE);//������һ�ν���
        }
    }
  /* USER CODE END UART7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
