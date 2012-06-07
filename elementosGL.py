
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
        return "" + str(self.x) + "; " + str(self.y) + "; " + str(self.z)+ ""

class Orientacao ():
    def __init__(self, x, y, z, w):
        self.x = x
        self.y = y
        self.z = z
        self.w = w
    def __repr__(self):
        return "" + str(self.x) + "; " + str(self.y) + "; " + str(self.z)+ "; " + str(self.w)+ ""

class Cor ():
    def __init__(self, r, g, b):
        self.r = r
        self.g = g
        self.b = b
    def __repr__(self):
        return "" + str(self.r) + "; " + str(self.g) + "; " + str(self.b)+ ""


class Elemento ():
    def __init__(self, nome, cor, espessura, tipo, angulacao, lstPontos):
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
        return "" + str(self.cod)               \
               + "; " + str(self.nome)          \
               + "; " + str(self.cor)           \
               + "; " + str(self.espessura)     \
               + "; " + tipo[self.tipo]         \
               + "; " + str(self.angulacao)     \
               + "; " + saida + ""                   

       

lst = []
lst.append(Elemento("L", Cor(255,0,0), 0, "xis", Orientacao(90, 0, 0, 90), [Ponto(0, 0, 0), Ponto(3, 3, 0)]))
print len(lst)
salva (lst)



'''
'P':  //Ponto
'L':  //Linha
'C':  //Circulo
'E':  //Esfera
'T':  //Triangulo
'R':  //Retangulo
'c':  //[c]one
't':  //[t]órus

'''
