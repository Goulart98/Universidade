def indice_builder(autores):
  autores_sorted = sorted(autores)
  indice_str = str()
  letra = None
  for autor in autores_sorted:
    if autor[0] != letra:
      letra = autor[0]
      indice_str += letra + '\n'
    if len(autores[autor]) == 1:
      indice_str += '{0} (1 entrada):\n'.format(autor)
    else:
      indice_str += '{0} ({1} entradas):\n'.format(autor,str(len(autores[autor])))

    for entrada in autores[autor]:
      indice_str += ' "{1}", {0}, {2}\n'.format(entrada[0],entrada[1],entrada[2])
    indice_str += '\n\n'
  
  return indice_str