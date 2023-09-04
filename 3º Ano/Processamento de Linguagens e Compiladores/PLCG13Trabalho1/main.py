#!/usr/bin/python
# -*- coding: utf8 -*-

import re
from auxFunc import addAutor
from html_builder import html_builder
from indice_builder import indice_builder
from graph_builder import graph_builder

f = open('exemplo-utf8.bib','r', encoding="utf8")

pattern_categorias = r'(@[\w]+{(.+\n)+}\n\n)'
pattern_nome_cat = r'(?<=@)[\w]+(?={)'
pattern_chave = r'(?<={)[\w:-]+(?=,\n)'
pattern_autor = r'author *= *({|"){*(([\w.\s]|,|-|\\\'|\\\~)+)(?=}|",\n)'
pattern_titulos = r' title *= *({|")((.*)|(.*\n.*)|(\n.*))(}|")' #nao deteta freq2002

categorias = re.findall(pattern_categorias,f.read())
f.close()
dict_aut = dict()
dict_cat = dict()
dict_aut_indice = dict()
#dict_cat {cat: [incidencia, {chave:[[autores],titulo]}]}

for categoria in categorias:
    categoria = categoria[0]
    categoria_nome = re.findall(pattern_nome_cat,categoria)[0].lower()
    
    chave = re.findall(pattern_chave,categoria)[0]
    autor = re.findall(pattern_autor,categoria, re.IGNORECASE)[-1][1]
    autores = re.split(r' *and +| +and\n *',autor,100,re.IGNORECASE)
    autores = addAutor(dict_aut, autores)
    incidencia = 1
    entradas = dict()

    try:
      titulo = re.findall(pattern_titulos,categoria, re.IGNORECASE)[0]
    except:
      continue

    if categoria_nome in dict_cat:
        incidencia += dict_cat[categoria_nome][0]
        entradas = dict_cat[categoria_nome][1]
        
    entradas[chave] = [autores,titulo]
    dict_cat[categoria_nome] = [incidencia,entradas]
    for autor in autores:
      if autor.lstrip() not in dict_aut_indice:
        dict_aut_indice[autor.lstrip()] = list()
      dict_aut_indice[autor.lstrip()].append([chave,titulo[1],categoria_nome])

html = html_builder(dict_cat)
open('index.html','w').write(html)
print("Ficheiro HTML criado com sucesso.")

indice_autores = indice_builder(dict_aut_indice)
open('indice_autores.txt','w').write(indice_autores)
print("Ficheiro TXT criado com sucesso.")

autor = input('Autor: ')
graph = graph_builder(dict_aut,autor)
open('graph.dot','w').write(graph)
print("Ficheiro DOT criado com sucesso.")