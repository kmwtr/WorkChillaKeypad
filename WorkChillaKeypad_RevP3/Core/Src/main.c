/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

extern USBD_HandleTypeDef hUsbDeviceFS;

#define rowNum 6    // 行 IN 0 to 5
#define colNum 10   // 列 OUT 0 to 9

// 行　上から下へ
const uint16_t rowPin[rowNum] =
{
        IN_0_Pin, IN_1_Pin, IN_2_Pin, IN_3_Pin, IN_4_Pin, IN_5_Pin
};
// 列　左から右へ
const uint16_t colPin[colNum] =
{
        OUT_0_Pin, OUT_1_Pin, OUT_2_Pin, OUT_3_Pin, OUT_4_Pin, OUT_5_Pin, OUT_6_Pin, OUT_7_Pin, OUT_8_Pin, OUT_9_Pin
};

// モディファイアキー
#define MOD_CTRL_L  0x01
#define MOD_SHIFT_L 0x02
#define MOD_ALT_L   0x04
#define MOD_META_L  0x08
#define MOD_CTRL_R  0x10
#define MOD_SHIFT_R 0x20
#define MOD_ALT_R   0x40
#define MOD_META_R  0x80

// 通常キー
#define KEY_NULL    0x00    // Reserved (no event indicated)

#define KEY_RIGHT   0x4F
#define KEY_LEFT    0x50
#define KEY_DOWN    0x51
#define KEY_UP      0x52

#define KEY_A       0x04
#define KEY_B       0x05
#define KEY_C       0x06
#define KEY_D       0x07
#define KEY_E       0x08
#define KEY_F       0x09
#define KEY_G       0x0A
#define KEY_H       0x0B
#define KEY_I       0x0C
#define KEY_J       0x0D
#define KEY_K       0x0E
#define KEY_L       0x0F
#define KEY_M       0x10
#define KEY_N       0x11
#define KEY_O       0x12
#define KEY_P       0x13
#define KEY_Q       0x14
#define KEY_R       0x15
#define KEY_S       0x16
#define KEY_T       0x17
#define KEY_U       0x18
#define KEY_V       0x19
#define KEY_W       0x1A
#define KEY_X       0x1B
#define KEY_Y       0x1C
#define KEY_Z       0x1D

#define KEY_1       0x1E
#define KEY_2       0x1F
#define KEY_3       0x20
#define KEY_4       0x21
#define KEY_5       0x22
#define KEY_6       0x23
#define KEY_7       0x24
#define KEY_8       0x25
#define KEY_9       0x26
#define KEY_0       0x27

#define KEY_RETURN  0x28
#define KEY_ESCAPE  0x29
#define KEY_DELETE  0x2A
#define KEY_TAB     0x2B
#define KEY_SPACE   0x2C

#define KEY_MINUS       0x2D    // - _
#define KEY_EQUAL       0x2E    // = +
#define KEY_BRACKET_L   0x2F    // [ {
#define KEY_BRACKET_R   0x30    // ] }
#define KEY_BACKSLASH   0x31    // '\' |
#define KEY_NONUS       0x32
#define KEY_SEMICOLON   0x33    // ; :
#define KEY_QUOTATION   0x34    // ' "
#define KEY_GRAVE       0x35    // ` ~
#define KEY_LTHAN       0x36    // less than '<'
#define KEY_GTHAN       0x37    // greater than '>'
#define KEY_SLASH       0x38    // / ?
#define KEY_CAPS        0x39    // CapsLock

#define KEY_F1      0x3A
#define KEY_F2      0x3B
#define KEY_F3      0x3C
#define KEY_F4      0x3D
#define KEY_F5      0x3E
#define KEY_F6      0x3F
#define KEY_F7      0x40
#define KEY_F8      0x41
#define KEY_F9      0x42
#define KEY_F10     0x43
#define KEY_F11     0x44
#define KEY_F12     0x45

#define KEY_BACKSP  0xBB

#define KEY_MENU    0x76
#define KEY_ZENKAKUHANKAKU  0x94 // Keyboard LANG5

// 通常キー 注意：ASCIIではない USB HID Usage Tables.pdf
const uint8_t workmanKeyMap[rowNum][colNum] =
{
        { KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_UP, KEY_NULL, KEY_ESCAPE, KEY_MENU, KEY_RETURN, KEY_DELETE, KEY_BACKSP },
        { KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0 },
        { KEY_Q, KEY_D, KEY_R, KEY_W, KEY_B, KEY_J, KEY_F, KEY_U, KEY_P, KEY_DELETE },
        { KEY_A, KEY_S, KEY_H, KEY_T, KEY_G, KEY_Y, KEY_N, KEY_E, KEY_O, KEY_I },
        { KEY_Z, KEY_X, KEY_M, KEY_C, KEY_V, KEY_K, KEY_L, KEY_LTHAN, KEY_GTHAN, KEY_RETURN },
        { MOD_SHIFT_L, KEY_TAB, MOD_ALT_L, MOD_CTRL_L, KEY_SPACE, KEY_SPACE, MOD_CTRL_R, MOD_ALT_R, KEY_ZENKAKUHANKAKU, MOD_SHIFT_R }
};

const uint8_t qwertyKeyMap[rowNum][colNum] =
{
        { KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_UP, KEY_NULL, KEY_ESCAPE, KEY_MENU, KEY_RETURN, KEY_DELETE, KEY_BACKSP },
        { KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0 },
        { KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_DELETE },
        { KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_P },
        { KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_LTHAN, KEY_GTHAN, KEY_RETURN },
        { MOD_SHIFT_L, KEY_TAB, MOD_ALT_L, MOD_CTRL_L, KEY_SPACE, KEY_SPACE, MOD_CTRL_R, MOD_ALT_R, KEY_ZENKAKUHANKAKU, MOD_SHIFT_R }
};

const uint8_t trrigerdKeyMap[rowNum][colNum] =
{
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,       KEY_NULL,       KEY_ESCAPE,     KEY_NULL,       KEY_NULL,       KEY_NULL,       KEY_NULL },
        { KEY_F1,   KEY_F2,   KEY_F3,   KEY_F4,         KEY_F5,         KEY_F6,         KEY_F7,         KEY_F8,         KEY_F9,         KEY_F10 },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_GRAVE,      KEY_GRAVE,      KEY_MINUS,      KEY_EQUAL,      KEY_MINUS,      KEY_EQUAL,      KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_BRACKET_L,  KEY_BRACKET_R,  KEY_BRACKET_L,  KEY_BRACKET_R,  KEY_BACKSLASH,  KEY_BACKSLASH,  KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_SEMICOLON,  KEY_SEMICOLON,  KEY_QUOTATION,  KEY_QUOTATION,  KEY_SLASH,      KEY_SLASH,      KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL }
};

const uint8_t trrigerdModMap[rowNum][colNum] =
{
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,     KEY_NULL,   KEY_NULL,   KEY_NULL,   KEY_NULL,   KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,     KEY_NULL,   KEY_NULL,   KEY_NULL,   KEY_NULL,   KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,     MOD_SHIFT_L, KEY_NULL,  KEY_NULL,   MOD_SHIFT_L, KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,     MOD_SHIFT_L, MOD_SHIFT_L, KEY_NULL, MOD_SHIFT_L, KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, MOD_SHIFT_L,  KEY_NULL,   MOD_SHIFT_L,    KEY_NULL, MOD_SHIFT_L, KEY_NULL },
        { KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL }
};

// キーの状態
uint8_t keyState[rowNum][colNum];

// 電気的な状態（回路 に 1:High がデフォルト
uint8_t currentState[rowNum][colNum];   // センシング結果 1度目
uint8_t temporaryState[rowNum][colNum]; // センシング結果 2度目
uint8_t beforeState[rowNum][colNum];    // 前回のセンシング結果

// キーレイアウトフラグ
uint8_t keyboardLayoutFlag = 0b00000000;    // 0 == qwerty

// テキトーディレイ
void delay_us(uint32_t i) {
    while (i > 0) {
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        i--;
    }
}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  // USB-HID
  // - - - - - - - - - - - - - - - - - - - - - - - -
  struct keyboardHID_t
  {
      // このサイズは必須らしい?
      uint8_t id;
      uint8_t modifires;
      uint8_t key1;
      uint8_t key2;
      uint8_t key3;
  };

  struct keyboardHID_t keyboardHID = { 1, 0, 0, 0, 0 };

  // Setup
  // - - - - - - - - - - - - - - - - - - - - - - - -
  uint32_t i = 0;
  uint32_t j = 0;

  // row はインプット。通常HIGH／スイッチ押下でLOW、が想定される

  // col をデフォルトHighに
  for (i = 0; i < colNum; i++) {
      HAL_GPIO_WritePin(GPIOA, colPin[i], 1);
  }

  // バッファに初期状態を入力
  for (i = 0; i < rowNum; i++) {
      for (j = 0; j < colNum; j++) {
          keyState[i][j] = 0;
          currentState[i][j] = 1;
          beforeState[i][j] = 1;
      }
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      // 電気的走査
      // - - - - - - - - - - -
      // 行を回す
      for (i = 0; i < rowNum; i++) {
          // カラムを回す
          for (j = 0; j < colNum; j++) {
              HAL_GPIO_WritePin(GPIOA, colPin[j], 0); // Lowでチェック
              delay_us(1);
              // row[i]の値をバッファに格納
              currentState[i][j] = HAL_GPIO_ReadPin(GPIOB, rowPin[i]);
              // チャタリング防止
              delay_us(1);
              // 再度チェック
              if (currentState[i][j] == HAL_GPIO_ReadPin(GPIOB, rowPin[i])) {
                  // かつ前回と変化があったかどうか
                  if (currentState[i][j] != beforeState[i][j]) {
                      // 押した or 放した
                      keyState[i][j] = 1 - currentState[i][j]; // 分かりやすさのために反転させて保存
                      // 格納
                      beforeState[i][j] = currentState[i][j];
                      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // Lチカデバッグ
                  }
              }
              HAL_GPIO_WritePin(GPIOA, colPin[j], 1); // �?フォル Highに戻す
          }
      }

      // データ走査
      // 一旦初期化
      keyboardHID.modifires = 0x00;
      keyboardHID.key1 = 0x00;

      // データの走査開始
      for (i = 0; i < rowNum; i++) {
          for (j = 0; j < colNum; j++) {
              if (keyState[i][j] == 1) {
                  // アクティブなキー
                  if (i == 5) {
                      if (j == 2 || j == 3 || j == 6 || j== 7 || j ==9) {
                          keyboardHID.modifires = qwertyKeyMap[i][j]; // モディファイアキー押下
                      }else if(j == 0){
                          // 特殊キートリガー
                          keyboardLayoutFlag = 1;
                      }else if (j == 8){
                          //keyboardLayoutFlag ^= 0b00000001;
                      }
                      else {
                          keyboardHID.key1 = qwertyKeyMap[i][j]; // 通常キー押下
                      }
                  } else {
                      if (keyboardLayoutFlag == 0){
                          keyboardHID.key1 = qwertyKeyMap[i][j]; // 通常キー押下
                      }else{
                          keyboardHID.modifires = trrigerdModMap[i][j]; // モディファイアキー押下
                          keyboardHID.key1 = trrigerdKeyMap[i][j]; // 通常キー押下
                          keyboardLayoutFlag = 0;
                          //keyboardHID.key1 = workmanKeyMap[i][j]; // Workmanキー押下
                      }
                  }
              }
          }
      }

      // 結果の送信(モディファイアとの関連性があるので、全体を検索したのちに送信すべき）（←？）
      USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof(struct keyboardHID_t));
      delay_us(10);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the SYSCFG APB clock
  */
  __HAL_RCC_CRS_CLK_ENABLE();
  /** Configures CRS
  */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000,1000);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 2;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, OUT_0_Pin|OUT_1_Pin|OUT_2_Pin|OUT_3_Pin
                          |OUT_4_Pin|OUT_5_Pin|OUT_6_Pin|OUT_7_Pin
                          |OUT_8_Pin|OUT_9_Pin|LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : OUT_0_Pin OUT_1_Pin OUT_2_Pin OUT_3_Pin
                           OUT_4_Pin OUT_5_Pin OUT_6_Pin OUT_7_Pin
                           OUT_8_Pin OUT_9_Pin LED_Pin */
  GPIO_InitStruct.Pin = OUT_0_Pin|OUT_1_Pin|OUT_2_Pin|OUT_3_Pin
                          |OUT_4_Pin|OUT_5_Pin|OUT_6_Pin|OUT_7_Pin
                          |OUT_8_Pin|OUT_9_Pin|LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SWICH_Pin IN_0_Pin IN_1_Pin IN_2_Pin
                           IN_3_Pin IN_4_Pin IN_5_Pin */
  GPIO_InitStruct.Pin = SWICH_Pin|IN_0_Pin|IN_1_Pin|IN_2_Pin
                          |IN_3_Pin|IN_4_Pin|IN_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TCM809_Pin */
  GPIO_InitStruct.Pin = TCM809_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TCM809_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
