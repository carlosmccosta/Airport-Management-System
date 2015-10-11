CFLAGS = -Wall

PROJ1_EXE = proj1_gestao_aero.exe

C_SRC = Aeroporto.cpp Aviao.cpp Companhia.cpp main.cpp Menu.cpp PortaEmbarque.cpp Exceptions.cpp Tripulante.cpp TipoAviao.cpp TipoAviaoDB.cpp Voo.cpp utils.cpp DataHora.cpp Passageiro.cpp Pessoa.cpp Atraso.cpp Comandos.cpp Hospedeiro.cpp Piloto.cpp GestaoAeroporto.cpp
C_OBJ = $(C_SRC:.cpp=.o)

all: $(PROJ1_EXE)

%.o: $(wildcard *.h)
%.o: %.c
	g++ $(CFLAGS) -c $<

$(PROJ1_EXE): $(C_OBJ)
	g++ $(CFLAGS) -o $@ $(C_OBJ)

clean:
	rm $(C_OBJ)
	rm $(PROJ1_EXE)

rebuild:
	$(MAKE) clean
	$(MAKE)
