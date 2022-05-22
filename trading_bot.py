#%% Librerias
from tradingview_ta import TA_Handler, Interval, Exchange
import constantes_acciones

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

#%% Function

def run_bot_for_ticker(ticker_info, interval = '5m'):
    """ Bot function that returns the investment recomendation
    
    Args:
        ccxt_ticker : string with the ccxt's ticker of the stock
    Returns:
        trade_rec_type: 'WAIT', 'BUY' or 'SELL' according to Technical Analysis
    """
    
    accion = TA_Handler(
        symbol = ticker_info['TICKER_NAME'],
        screener = ticker_info['screener'],
        exchange=ticker_info['exchange'],
        interval = interval,
    )

    analysis = accion.get_analysis().summary
    print(analysis)
    recom = analysis["RECOMMENDATION"]
    print(recom)
    if recom == 'STRONG_SELL' or recom == 'SELL':
        return 'S'
    elif recom == 'STRONG_BUY' or recom == 'BUY':
        return 'B'
    elif recom == 'NEUTRAL':
        return 'W'


# %% Running
# ticker_info = constantes_acciones._johnson_
# run_bot_for_ticker(ticker_info, interval=INTERVAL_1_DAY)
