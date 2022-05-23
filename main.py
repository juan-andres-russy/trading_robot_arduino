from pyfirmata import Arduino, util, STRING_DATA
import time
import keyboard
from trading_bot import run_bot_for_ticker
import constantes_acciones

board = Arduino('COM3')

#%% Intevals
INTERVAL_1_MINUTE = "1m"
INTERVAL_5_MINUTES = "5m"
INTERVAL_15_MINUTES = "15m"
INTERVAL_30_MINUTES = "30m"
INTERVAL_1_HOUR = "1h"
INTERVAL_2_HOURS = "2h"
INTERVAL_4_HOURS = "4h"
INTERVAL_1_DAY = "1d"
INTERVAL_1_WEEK = "1W"
INTERVAL_1_MONTH = "1M"

#%% Loop de busqueda
while True:
    ticker_info = constantes_acciones._johnson_
    string = run_bot_for_ticker(TICKER_NAME, INTERVAL_5_MINUTES)
    board.send_sysex(STRING_DATA, util.str_to_two_byte_iter(string))
    time.sleep(1)
    if keyboard.read_key() == "p":
        print("Exit...")
        break
    
board.exit()


