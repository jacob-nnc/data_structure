class matchcell():
    def __init__(self,lis=[],value='\0') -> None:
        self.lis=lis
        self.value=value
    def chuli(self,a:str):
        if a=='.':
            pass
class matchexpr():
    def __init__(self,expr:str) -> None:
        self.expr=expr
        self.match_list=[]
        self.help_list=[]
        self.HELP_LIST=list('*+?{}')
    def devide(self):
        for i in range(len(self.expr)):
            if self.expr[i]=='.':

expr='[+-]?[0-9]+'