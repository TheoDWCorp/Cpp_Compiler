# Lexique


La table d'association entre pattern et token.

**lexeme** : portion du code source qui match un pattern

**pattern** : regex qui represente la forme d'un lexeme. Dans le cas d'un *keyword*, le pattern est identique au *lexeme*.

**token** : objet qui décrit un lexeme au parser et qui contient les informations pertinante ( ligne de lecture , valeur de la constante, ligne dans la table des symboles, etc.)

*source : p134 DragonBook*

---
Les patterns sont groupé en différentes classe : **keyword**, **operateur** , **constante** , **identifiant**.

## Keyword 

Les mots clés du langage ada et leur indice 

- and : 0
- begin :1
- else : 2
- elsif : 3
- end : 4
- for : 5
- function : 6
- if : 7
- in : 8
- is : 9
- loop : 10 
- not : 11
- null : 12
- or : 13
- out : 14
- procedure : 15
- record : 16
- rem : 17
- return : 18
- reverse : 19
- then : 20
- type : 21
- use : 22
- while : 23
- with : 24


keyword non reconu : 
- access
- new

## Operateur 

Les opérateurs du langage : 
- \+  : 30
- \-  : 31
- /   : 32
- \*  : 33
- <   : 34
- \>  : 35
- =   : 36
- /=  : 37
- <=  : 38
- \>= : 39
- :=  : 40

## Séparateurs

- `:`  : 41
- ; : 42
- ( : 43
- ) : 44
- . : 45
- , : 46
## Constante 
5 types de constante : `char`, `integer`, `float`, `boolean` et `string`.  
identifiant : 45
### char
regex : '[A-Z]|[a-z]'  
### integer :
regex : [-]?[1-9]+  
attention à la lecture du '-'
### float
regex : [-]?[1-9]+\\.[1-9]+  
attention à la lecture du '-'
### boolean 
regex : true | false  

### string 
regex : "[^"]*"  
attention : cas ""(string vide)

## Identifiant
index : 55  
regex : ( [ a - z ] | [ A - Z ] ) ( [ A - Z ] | [ a - z ] | _ )*  
Pour les variables, les functions, les procédures, les types

### Attribut des idf :
- indice dans la table des symboles
