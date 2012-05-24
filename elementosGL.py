
NUM_ELEMENTOS = 0


tipo = dict()
tipo["circulo"] = '''010111010'''
tipo["xis"] = '''101010101'''

def salva (lstElemento):
    arq = open("lstElementos.txt", "w")
    saida = ""
    for elemento in lstElemento:
        saida += str(elemento) + "\n"
    print saida
    arq.write(saida)
    arq.close()
    
class Ponto ():
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
    def __repr__(self):
        return "" + str(self.x) + ", " + str(self.y) + ", " + str(self.z)+ ""

class Cor ():
    def __init__(self, r, g, b):
        self.r = r
        self.g = g
        self.b = b
    def __repr__(self):
        return "" + str(self.r) + ", " + str(self.g) + ", " + str(self.b)+ ""


class Elemento ():
    def __init__(self, nome, lstPontos, cor, espessura, angulacao, tipo):
        global NUM_ELEMENTOS
        self.cod = NUM_ELEMENTOS
        self.nome = nome
        self.lstPontos = lstPontos
        self.cor = cor
        self.espessura = espessura
        self.angulacao = angulacao
        self.tipo = tipo
        NUM_ELEMENTOS+=1
    def __repr__(self):
        saida = ""
        for ponto in self.lstPontos:
            saida += str(ponto) + ", "
        return "" + str(self.cod)              \
               + "; " + str(self.nome)           \
               + "; " + saida                    \
               + str(self.cor)                   \
               + "; " + str(self.espessura)      \
               + "; " + str(self.angulacao)      \
               + "; " + tipo[self.tipo] + ""
       

lst = []
lst.append(Elemento("Linha", [Ponto(0, 0, 0), Ponto(3, 3, 0)], Cor(255, 0, 0), 1, Ponto(90, 0, 0), "xis"))
lst.append(Elemento("Linha", [Ponto(5, 5, 0), Ponto(0, 0, 0)], Cor(255, 0, 0), 2, Ponto(0, 90, 0), "circulo"))
lst.append(Elemento("Linha", [Ponto(5, 5, 0), Ponto(0, 0, 0)], Cor(255, 0, 0), 3, Ponto(0, 0, 90), "circulo"))
salva (lst)
