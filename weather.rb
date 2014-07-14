# -*- coding: utf-8 -*-
require 'open-uri'
require 'nokogiri'
require 'digiusb'

# Digisparkを使う準備
spark = DigiUSB.sparks.first

# 天気予報URL
url = 'http://weather.yahoo.co.jp/weather/jp/9/4110.html'

# 文字コード設定と読み込み
charset = nil
html = open(url){ |f|
  charset = f.charset
  f.read
}

# ループ
loop {

  # 読み込み
  doc = Nokogiri::HTML.parse(html, nil, charset)

  # 雨が入る、曇が入る、晴れが入るという優先順位で書き込み
  if doc.search("p.pict")[1].text.include?("雨")
    spark.write('r');
  elsif doc.search("p.pict")[1].text.include?("曇")
    spark.write('c');
  elsif doc.search("p.pict")[1].text.include?("晴")
    spark.write('s');
  end

  sleep 30
  spark.write('x');

  # アクセスは1分ごと
  sleep 30
}
