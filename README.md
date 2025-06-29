Projeto: Registro de Doadores para ONG
Este é um projeto desenvolvido para a disciplina de Linguagem de Programação da Fatec Arthur de Azevedo - Mogi Mirim,
sob a orientação do Prof. Me. Marcos Roberto de Moraes. O objetivo é aplicar conceitos de estruturas de dados,
manipulação de arquivos e práticas de desenvolvimento de software em C.

Tema Escolhido: Registro de Doadores para ONG
Este projeto implementa um sistema de gerenciamento para o cadastro de doadores de uma Organização Não Governamental (
ONG). O sistema permite o controle de doadores com informações como nome completo, e-mail, telefone, valor da última
doação e a data em que foi realizada.

Funcionalidades Implementadas
Cadastro de novos doadores: Permite a inserção de novos doadores no sistema com validação de dados.

Consulta de doadores: Busca de um doador específico pelo seu e-mail.

Atualização de dados: Permite editar as informações de um doador já cadastrado.

Remoção de doadores: Exclui o registro de um doador do sistema após confirmação.

Listagem do Top 10 Doadores: Gera um relatório ordenado com os 10 doadores que mais contribuíram financeiramente.

Estrutura de Dados
Os dados dos doadores são armazenados de forma persistente em um arquivo de texto no formato CSV (Comma-Separated
Values), chamado doadores.csv. Para operações que exigem a manipulação de múltiplos registros, como a geração do Top 10,
os dados são carregados do arquivo para um array de structs na memória para serem processados e ordenados.

Como Baixar e Compilar
Clone o repositório para a sua máquina local:

Bash

git clone https://github.com/MathiasRibeirao/trabalhoMaromo.git
cd trabalhoMaromoFinal
(Lembre-se de substituir o link e o nome da pasta se forem diferentes)

Compile o código. Certifique-se de ter um compilador C (como o GCC) instalado. O comando deve incluir todos os seus
arquivos .c:

Bash

gcc -o gestor_doadores main.c doador.c tratamento_entrada.c -Wall
A flag -Wall é uma boa prática que ativa todos os avisos (warnings) do compilador, ajudando a encontrar possíveis
problemas no código.

Como Testar
Execute o programa compilado a partir do terminal:

No Windows:

Bash

.\doadores.exe
No Linux ou macOS:

Bash

./gestor_doadores
Siga as instruções do menu interativo no console para realizar as operações de gerenciamento de doadores.

Autores
Mathias Ribeiro

Kauê Domingos Padilha

Lucas Freire Negri

Carlos Gabriel Simões

Gabriel Filipe Calisto