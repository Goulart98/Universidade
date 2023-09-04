Minha resolução do teste 2022-2023 parte 2

package com.teste.app;

import java.time.LocalDate;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class GestaoTrabalhos {
  private Map<String, Aluno> alunos;
  private Map<String, Grupo> grupos;
  private LocalDate dataLimite;

  // Questão 6

  public GestaoTrabalhos() {
    this.alunos = new HashMap<>();
    this.grupos = new HashMap<>();
    this.dataLimite = LocalDate.of(2024, 1, 1);
  }

  public GestaoTrabalhos(Collection<Aluno> alunos, Map<String, String> alunosGrupo, LocalDate dataLimite) {
    this.alunos = new HashMap<>();
    this.grupos = new HashMap<>();

    for (Aluno a : alunos) {
      this.alunos.put(a.getCodAluno(), a.clone());

      String codGrupoDoAluno = alunosGrupo.get(a.getCodAluno());
      Grupo grupoExiste = this.grupos.get(codGrupoDoAluno);

      if (grupoExiste == null) {
        grupoExiste = new Grupo(codGrupoDoAluno);
      }

      this.grupos.put(grupoExiste.getCodGrupo(), grupoExiste.clone());
      a.registra(grupoExiste);
    }

    this.dataLimite = dataLimite;
  }

  public Map<String, Grupo> getGrupos() {
    return grupos;
  }

  public LocalDate getDataLimite() {
    return dataLimite;
  }

  public void setDataLimite(LocalDate dataLimite) {
    this.dataLimite = dataLimite;
  }

  public void adicionaAluno(Aluno a) throws AlunoJaInscritoError {
    if (this.alunos.containsKey(a.getCodAluno())) {
      throw new AlunoJaInscritoError();
    }

    Grupo grupoAluno = a.getMeuGrupo();
    if (!this.grupos.containsKey(grupoAluno.getCodGrupo())) {
      this.grupos.put(grupoAluno.getCodGrupo(), grupoAluno.clone());
    }

    this.alunos.put(a.getCodAluno(), a.clone());
  }

  // Questão 7

  public Entrega melhorEntrega() {
    Entrega melhor = null;
    Grupo melhorGrupo = null;

    for (Grupo g : grupos.values()) {
      for (Entrega e : g.getEntregas()) {
        if (melhor == null && melhorGrupo == null) {
          melhor = e;
          melhorGrupo = g;
        } else if (e.calculaNotaEntrega() > melhor.calculaNotaEntrega()) {
          melhor = e;
          melhorGrupo = g;
        } else if (e.calculaNotaEntrega() == melhor.calculaNotaEntrega() &&
            g.getCodGrupo().compareTo(melhorGrupo.getCodGrupo()) < 0) {
          melhor = e;
          melhorGrupo = g;
        }
      }
    }

    System.out.println("Melhor entrega do grupo: " + melhorGrupo.getCodGrupo());
    return melhor;
  }

  // Questão 8

  public void adicionaEntrega(String codGrupo, Entrega e) throws GrupoNaoExisteError, AvaliadorError, DataError {
    Grupo grupo = this.grupos.values().stream()
        .filter(g -> g.getCodGrupo().equals(codGrupo))
        .findFirst()
        .orElse(null);

    if (grupo == null) {
      throw new GrupoNaoExisteError(codGrupo);
    }

    Aluno avaliador = e.getAvaliador();
    if (avaliador.getMeuGrupo().equals(grupo)) {
      throw new AvaliadorError();
    }

    if (e.getData().compareTo(this.dataLimite) > 0) {
      throw new DataError();
    }

    grupo.addEntrega(e);
  }
}

  // Questão 10

  public class GestaoRelaxadaTrabalhos extends GestaoTrabalhos {
  private Map<String, List<Entrega>> entregasAtrasadas;

  public GestaoRelaxadaTrabalhos() {
    super();
    this.entregasAtrasadas = new HashMap<>();
  }

  public GestaoRelaxadaTrabalhos(Collection<Aluno> alunos, Map<String, String> alunosGrupo, LocalDate dataLimite) {
    super(alunos, alunosGrupo, dataLimite);
    this.entregasAtrasadas = new HashMap<>();
  }

  @Override
  public void adicionaEntrega(String codGrupo, Entrega e) throws GrupoNaoExisteError, AvaliadorError {
    Grupo grupo = super.getGrupos().values().stream()
        .filter(g -> g.getCodGrupo().equals(codGrupo))
        .findFirst()
        .orElse(null);

    if (grupo == null) {
      throw new GrupoNaoExisteError(codGrupo);
    }

    Aluno avaliador = e.getAvaliador();
    if (avaliador.getMeuGrupo().equals(grupo)) {
      throw new AvaliadorError();
    }

    if (e.getData().compareTo(super.getDataLimite()) > 0) {
      List<Entrega> entregasAtrasadas = this.entregasAtrasadas.get(codGrupo);
      if (entregasAtrasadas == null) {
        entregasAtrasadas = new ArrayList<>();
        this.entregasAtrasadas.put(codGrupo, entregasAtrasadas);
      }

      entregasAtrasadas.add(e); // e.clone()
      grupo.addEntrega(e);
    }

    // Salva entrega
    try (FileOutputStream fos = new FileOutputStream(codGrupo + super.getDataLimite().toString());
        ObjectOutputStream oos = new ObjectOutputStream(fos)) {

      oos.writeObject(e);
    } catch (IOException exception) {
      throw new RuntimeException(exception);
    }
  }
}