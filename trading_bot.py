#%% Librerias

from datetime import datetime  # Fechas
import pandas as pd  # Manejo de bases de datos
import numpy as np  # Manejo de vectores
import ccxt  # Exchange de crypto
import talib # Libreria de Analisis Tecnico
import yfinance # Exchange de stock

#%% Variables
CANDLE_DURATION_IN_MIN = '5m' # Minutos en los que se realiza el Analisis Tecnico

# Indicador de fuerza de compra relativa
RSI_PERIOD = 14
RSI_OVERBOUGHT = 70
RSI_OVERSOLD = 30

# Tickers
TYPE_TICKER = 'stock'  # 'stock' or 'crypto'
TICKER_NAME = 'SOL'  # 'ETH/USDT'

# Conexion con Binance
exchange = ccxt.binance()  


#%% Funciones

def fetch_data(ticker, type_ticker):
    """ Saca la informacion disponible en Binance
    
    Args:
        ticker : string with the ccxt's ticker of the stock
        type_ticker : 'stock' or 'crypto'
    Returns:
        ticker_df : dataframe with the ticker information.
    """
    
    if type_ticker == 'crypto':
        global exchange
        bars, ticker_df = None, None
    
        try:
            bars = exchange.fetch_ohlcv(
                ticker, timeframe=f'{CANDLE_DURATION_IN_MIN}', limit=100)
        except:
            print(f"Error in fetching data from the exchange:{ticker}")
    
        if bars is not None:
            ticker_df = pd.DataFrame(
                bars[:-1], columns=['at', 'open', 'high', 'low', 'close', 'vol'])
            ticker_df['Date'] = pd.to_datetime(ticker_df['at'], unit='ms')
            ticker_df['symbol'] = ticker
            print(ticker_df.columns)
    elif type_ticker == 'stock':
        try:
            ticker_df = yfinance.download(ticker, period = '5d', interval = f'{CANDLE_DURATION_IN_MIN}')
        except:
            print(f"Error in fetching data from the exchange:{ticker}")
    return ticker_df

# For period and interval information read https://algotrading101.com/learn/yfinance-guide/

def get_trade_recommendation(ticker_df):
    """ 
    Args:
        ticker_df    : dataframe with the ticker information.
    Returns:
        final_result : 'WAIT', 'BUY' or 'SELL' according to Technical Analysis
    """
    
    macd_result = 'WAIT'
    final_result = 'WAIT'

    # BUY or SELL based on MACD crossover points and the RSI value at that point
    try:
        macd, signal, hist = talib.MACD(  # stock
            ticker_df['Close'], fastperiod=12, slowperiod=26, signalperiod=9)
    except:
        macd, signal, hist = talib.MACD(  # crypto
            ticker_df['close'], fastperiod=12, slowperiod=26, signalperiod=9)
        
    last_hist = hist.iloc[-1]
    prev_hist = hist.iloc[-2]
    
    if not np.isnan(prev_hist) and not np.isnan(last_hist):
        # If hist value has changed from negative to positive or vice versa, it indicates a crossover
        macd_crossover = (abs(last_hist + prev_hist)
                          ) != (abs(last_hist) + abs(prev_hist))
        if macd_crossover:
            macd_result = 'BUY' if last_hist > 0 else 'SELL'

    if macd_result != 'WAIT':
        try:
            rsi = talib.RSI(ticker_df['Close'], timeperiod=14)  # stock
        except:
            rsi = talib.RSI(ticker_df['close'], timeperiod=14)  # crypto
            
        # Consider last 3 RSI values
        last_rsi_values = rsi.iloc[-3:]

        if (last_rsi_values.min() <= RSI_OVERSOLD):
            final_result = 'BUY'
        elif (last_rsi_values.max() >= RSI_OVERBOUGHT):
            final_result = 'SELL'

    return final_result


def run_bot_for_ticker(ticker_name, type_ticker):
    """ Bot function that returns the investment recomendation
    
    Args:
        ccxt_ticker : string with the ccxt's ticker of the stock
    Returns:
        trade_rec_type: 'WAIT', 'BUY' or 'SELL' according to Technical Analysis
    """
    
    ticker_data = fetch_data(ticker_name, type_ticker)
    
    if ticker_data is not None:
        print(ticker_data)
        trade_rec_type = get_trade_recommendation(ticker_data)
        print(
            f'{datetime.now().strftime("%d/%m/%Y %H:%M:%S")} \
            TRADING RECOMMENDATION: {trade_rec_type}')
        return trade_rec_type
    else:
        print(f'Unable to fetch ticker data - {ticker_name}. Retrying!!')

# %% Running
run_bot_for_ticker(TICKER_NAME, TYPE_TICKER) #CCXT_TICKER_NAME)
