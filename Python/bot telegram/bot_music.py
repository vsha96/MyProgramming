# -*- coding: utf-8 -*-
import telebot
import time
import eventlet
import requests
import logging
import config

bot = telebot.TeleBot(config.token)

@bot.message_handler(commands=['test'])
def find_file_ids(message):
    file_id = 'AwADAgADHQADyxdgS72XB5BHaFgmAg'
    res = bot.send_voice(message.chat.id, file_id, None)
    print(res)
time.sleep(3)

if __name__ == '__main__':
    bot.polling(none_stop=True)