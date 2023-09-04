import re

def addAutor(dic_aut,autores):
  for x in range(len(autores)):
    autores[x] = re.split(r', ',autores[x],re.IGNORECASE)
    if len(autores[x]) == 2:
      autores[x] = autores[x][1] + ' ' + autores[x][0]
    else:
      autores[x] = autores[x][0]

  if '' in autores:
    autores.remove('')

  for autor1 in autores:
    for autor2 in autores:
      autor1 = ' '.join(re.split(r'\n+ *',autor1,re.IGNORECASE))
      autor2 = ' '.join(re.split(r'\n+ *',autor2,re.IGNORECASE))
      if autor1 != autor2:
        if autor1 not in dic_aut:
          dic_aut[autor1] = list()
        dic_aut[autor1].append(autor2)

  return autores