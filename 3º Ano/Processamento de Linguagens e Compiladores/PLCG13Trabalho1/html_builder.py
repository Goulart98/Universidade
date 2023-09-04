def html_builder(dict_cat):
  html = '''<!DOCTYPE html>
  <html>
    <head>
      <style>
        .tabcen {
          text-align: center;
        }
          td,th {
          border: 1px solid grey;
        }
        th {
          background-color: #80808054;
        }
        .bortop {
          border-top: 5px solid black;
        }
        .borbot {
          border-bottom: 2px solid black;
        }
      </style>
    <body>
      <table>
        <tbody>'''

  for categoria in dict_cat:
      html += '''
          <tr>
            <th class="bortop">Categoria</th>
            <td class="tabcen bortop" colspan="2">{0}</td>
          </tr>'''.format(categoria)
      html += '''
          <tr>
            <th class="borbot">Incidencia</th>
            <td class="tabcen borbot" colspan="2">{0}</td>
          </tr>'''.format(str(dict_cat[categoria][0]))
      html += '''
          <tr>
            <th>Chave</th>
            <th>Autores</th>
            <th>Titulos</th>
          </tr>
              '''
      entradas = dict_cat[categoria][1]

      for entrada in entradas:
            html += '''
          <tr>
            <td>{0}</td>'''.format(entrada)
            lista_autores = '''
            <ul>'''
            for autor in entradas[entrada][0]:
              lista_autores += '''
              <li>{0}</li>'''.format(autor)
            lista_autores += '''
            </ul>'''
            html += '''
            <td>{0}</td>'''.format(lista_autores)
            html += '''
            <td>{0}</td>'''.format(entradas[entrada][1][1])

  html += '''
      </tbody>
    </table>
  </body>
</html>'''
  return html