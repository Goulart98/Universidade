def graph_builder(dict_aut,autor):
  for autor1 in dict_aut:
    dict_aut_temp = dict_aut[autor1]
    for autor2 in dict_aut_temp:
      if dict_aut[autor1].count(autor2) < 2:
        dict_aut[autor1].remove(autor2)
    dict_aut[autor1] = set(dict_aut[autor1])
  
  graph_dot = "digraph G {\n"

  if autor:
    for autor2 in dict_aut[autor]:
        graph_dot += '"{0}" -> "{1}"\n'.format(autor,autor2)
  else:
    for autor1 in dict_aut:
      for autor2 in dict_aut[autor1]:
        graph_dot += '"{0}" -> "{1}"\n'.format(autor1,autor2)

  graph_dot += "}"
  
  return graph_dot