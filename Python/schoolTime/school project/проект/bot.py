# -*- coding: utf-8 -*-
import config
import time
from config import number, markups, retreat
import basecsv
import basetime
import telebot
from telebot import types
bot = telebot.TeleBot(config.token)
markup = types.ReplyKeyboardMarkup()
keyboard_hider = types.ReplyKeyboardRemove()

@bot.message_handler(commands=["start","help"])
def hello(message):
    bot.send_message(message.chat.id, 'Привет! Я - бот :) \n Набери команду\n/remind , и я покажу какой сейчас урок \n/timetable , и я покажу тебе расписание на неделю \n /today - покажу расписание на сегодня \n /tomorrow - на завтра')
    file = open('members/' + str(message.chat.id) + '.txt','w')
    file.close()

@bot.message_handler(commands=["remind"])
def reminder(message):
    result = basetime.read_time()
    bot.send_message(message.chat.id, result)

@bot.message_handler(commands=["timetable"])
def timetable(message):
    result = basecsv.read_timetable()
    bot.send_message(message.chat.id, result)


@bot.message_handler(commands=["today"])
def today(message):
    pass

@bot.message_handler(commands=["tomorrow"])
def tomorrow(message):
    pass

@bot.message_handler(content_types=['text'])
def request(message):
    pass

@bot.message_handler(content_types=['sticker'])
def other_message(message):
    bot.send_message(message.chat.id, 'Ха-ха')

if __name__ == '__main__':
    bot.polling(none_stop=True)
    global glob
    glob = 0