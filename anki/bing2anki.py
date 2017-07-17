#-*- coding:utf-8 -*-
import splinter
import re
import os
import sys
import urllib3
import codecs
import shutil
from time import sleep

# definitions at most:3
def_limit=3
# column separator 
col_sep = '|'

re_empty_line = re.compile(r'^\s*$')

def bing_dict(browser, words_list):
    fields_xpath=(
                '//div[@class="hd_prUS"]',      # pronounce
                '//ul/li/span[@class="pos"]',   # POS, part of speech
                '//ul/li/span[@class="def"]',   # definition 
                '//div[@class="img_area"]/div[@class="simg"]/a/img[@class="rms_img"]'  # image , if have
                )
    browser.visit('http://cn.bing.com/dict/')
    sleep(5) # wait for page loading to complete
    i=0
    for each_word in words_list:
        if re_empty_line.match(each_word) is not None: continue
        i+=1
        if i%10 == 0:
            sleep(30) # webdriver makes too much short connections, wait all the TIME_WAIT to finish to avoid port exceeding
        browser.fill('q', each_word)
        button = browser.find_by_id('sb_form_go')
        button.click()
        browser_data=[]
        for xpath in fields_xpath:
            try:
                field = browser.find_by_xpath(xpath)
            except AttributeError as a:
                field = None
                pass
            browser_data.append(field)
        yield [each_word] +browser_data


def input_words_list(input_file):
    re_en_word=re.compile(r'^[a-zA-Z]+$')
    re_space = re.compile(r'\s+')
    for each_line in input_file: 
        if re_empty_line.match(each_line.rstrip()):
            continue
        words=re_space.split(each_line)
        if len(words) <1:continue
        en_words= []
        phrase=False
        for each_word in words:
            if re_en_word.match(each_word):
                phrase=True
                en_words.append(each_word)
            else:
                if phrase:
                    break
                else:
                    continue
        yield ' '.join(en_words)


def list_all(path, followlinks=False):
    name_path = {}
    for base_dir, sub_dir, files in os.walk(path, followlinks=followlinks):
        for f in files:
            name_path[f ] = os.path.join(base_dir, f)
        for f in sub_dir:
            name_path.update(list_all(os.path.join(base_dir, f)))
    return name_path


def format_anki(words_list, browser, voice_files, media_dir):
    http=urllib3.PoolManager()
    global def_limit
    global col_sep
    text_extractor = lambda t:t.text if t else ' '
    #word,pron,pos,def,img
    for each_word in bing_dict(browser, words_list):
        word = each_word[0]
        pron = text_extractor(each_word[1])
        try :
            voice_file = voice_files[word]
            voice = '[sound:{0}]'.format(os.path.basename(voice_file))
            shutil.copy(voice_file, media_dir)
        except  KeyError as k:
            voice = ''
        pos = list()
        defi = list()
        for i in range(def_limit):
            pos.append( '' if i >= len(each_word[2]) else text_extractor(each_word[2][i]))
            defi.append( '' if i >= len(each_word[3]) else text_extractor(each_word[3][i]))
        #print(word,pos, defi)
        #retrieve image via http(if have)
        imgs=each_word[4]
        anki_img=''
        if len(imgs):
            http_img = http.request('GET',imgs[0]['src'])
            img_suffix=http_img.headers.get('Content-Type').split('/')[1]
            img_name=word+'.'+img_suffix
            anki_img =os.path.join(media_dir, img_name) 
            f=open(anki_img, 'wb')
            f.write(http_img.data)
            f.close()
            http_img.release_conn()
            anki_img = '<img src="{0}">'.format(img_name)
        pdstrs=[]
        for pd in zip(pos,defi):
            pdstrs += pd
        yield [word, pron,voice] +pdstrs +[anki_img]


def create_anki_file(input_words, voice_path, browser, media_dir):
    anki_file = 'anki_bing.txt'
    voice_files=list_all(voice_path)
    re_suffix = re.compile(r'\.[^.]+$')
    if not voice_path.startswith(os.path.abspath(voice_path)):
        voice_files_nosuff={re_suffix.sub('',k):os.path.abspath(v) for k,v in voice_files.items()}
    else:
        voice_files_nosuff={re_suffix.sub('',k):v for k,v in voice_files.items()}
    #to check if anki_bing.txt exists , if so , continue with the end of file
    to_do_words  = list()
    done_list = list()
    if os.access(anki_file, os.R_OK):
        print('Previous {0} found, will continue with it, if you want start over, break and delete it then restart the progress'.format( anki_file), file=sys.stderr) 
    with codecs.open('anki_bing.txt', 'a+', 'utf-8') as anki_file:
        anki_file.seek(0)
        done_list  = [line.split(col_sep)[0] for line in anki_file]
        to_do_words = [word for word in input_words if word not in done_list]
        for anki_line in format_anki(to_do_words, browser, voice_files_nosuff, media_dir):
            anki_file.write(col_sep.join(anki_line) )
            anki_file.write('\n')

if __name__ == '__main__':
    voice_path = sys.argv[1]
    media_dir = os.path.join(os.getcwd(), 'anki_media')
    if not os.access(media_dir, os.R_OK):
        os.mkdir(media_dir)
    elif not os.path.isdir(media_dir):
        print('{0} is not a directory, please choose a directory to save image'.format(media_dir), file=sys.stderr)
        os.exit(1)
    else:
        pass
    browser = splinter.Browser(driver_name='chrome')
    input_words = input_words_list(sys.stdin)
    create_anki_file(input_words, voice_path, browser, media_dir)
    browser.quit()

