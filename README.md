<h1 align="center">Projeto de Animações e Controle de LEDs-Embarcatech 💻</h1>

<p>Este projeto envolve o uso de um microcontrolador para controlar uma matriz de LEDs e um buzzer, além de interagir com um teclado matricial. O objetivo principal é criar animações visuais nos LEDs e produzir sons com o buzzer em resposta à interação do usuário.</p>

<h2>Funções e Membros</h2>
<table border="1">
    <tr>
        <td>Líder: </td>
        <td>Mariana Barretto</td>
    </tr>
	 </tr>
       <tr>
        <td>Criação do Repositório, Gravação dos Vídeos e uma animação</td>
        <td>Mariana Barretto</td>
    </tr>
    <tr>
        <td> README.md e uma animação</td>
        <td>Alexandro Soares</td>
    </tr>
   <tr>
        <td> README.md e uma animação</td>
        <td>Ylo Bittencourt</td>
    </tr>
        <tr>
        <td>Ações das teclas D e * e uma animação</td>
        <td>Lucas Moreira</td>
    </tr>
    <tr>
        <td>Ações das teclas A e # e uma animação</td>
        <td>Helen Santos</td>
    </tr>
        <tr>
        <td>Definir a função de cada tecla e animação</td>
        <td>Edna Rodrigues</td>   
    <tr>
        <td>Ações das teclas B e C e uma animação</td>
        <td>Kauan Farias</td>
    </tr>
	<tr>
        <td>Diagram.json</td>
        <td>Daniel Santos</td>
    </tr>
  <tr>
        <td> Uma animação</td>
        <td>Israel Falcão</td>
    </tr> 
   </table>

<h2>Funcionalidades</h2>

<ul>
    <li><strong>Animações nos LEDs:</strong> Diversas animações podem ser exibidas na matriz de LEDs, incluindo setas, carinhas e corações.</li>
    <li><strong>Controle de Cores dos LEDs:</strong> O sistema permite alterar a cor dos LEDs (vermelho, verde, azul, etc.) com diferentes intensidades.</li>
    <li><strong>Teclado Matricial:</strong> O teclado matricial permite ao usuário selecionar diferentes opções de animação ou controle dos LEDs.</li>
    <li><strong>Buzzer:</strong> O buzzer é utilizado para tocar melodias, como uma sequência de notas musicais e efeitos sonoros.</li>
</ul>

<h2>Estrutura do Código</h2>

<p>O código é dividido em diversas seções, com destaque para:</p>

<ul>
    <li><strong>Configuração de Pinos e Clock:</strong> A configuração dos pinos GPIO é feita para controlar tanto a matriz de LEDs quanto o teclado matricial e o buzzer.</li>
    <li><strong>Funções de Animação:</strong> São definidas várias animações, como setas, corações, e outras formas visuais exibidas na matriz de LEDs.</li>
    <li><strong>Função de Melodia:</strong> A função de melodia permite tocar notas musicais através do buzzer.</li>
</ul>

<h2>Tecnologias</h2>
<ul>
  <li><strong>Raspberry Pi Pico W</strong> - A placa de desenvolvimento baseada no microcontrolador que é a base do projeto.</li>
  <li><strong>Pico SDK</strong> - O kit de desenvolvimento de software da Raspberry Pi Pico para programar o RP2040.</li>
  <li><strong>Linguagem de Programação C</strong> - Utilizada para o desenvolvimento do código do projeto.</li>
  <li><strong>GPIO (General Purpose Input/Output)</strong> - Para interação com hardware externo, como o teclado matricial, LEDs e buzzer.</li>
   <li><strong>Git</strong>: Sistema de controle de versão para gerenciar o código-fonte.</li>
   <li><strong>GitHub</strong>: Plataforma para hospedar e colaborar no repositório do projeto.</li>
  <li><strong>Teclado Matricial 4x4</strong> - Um componente para input de dados pelo usuário.</li>
  <li><strong>LED 5x5</strong> - Utilizado para criar as animações e definir cores.</li>
  <li><strong>Buzzer</strong> - Para emitir sons de alerta ou feedback.</li>  
<li><strong>Wokwi Integrado ao Visual Studio Code</strong> - Wokwi integrado ao Visual Studio Code para testar circuitos e projetos em microcontroladores, utilizado para a simulação e visualização do circuito na prórpia IDE.</li>
  <li><strong>CMake</strong> - Ferramenta de automação de construção usada para gerenciar o processo de compilação do código.</li>
 </ul>

<h2>Imagem</h2>
   
  ![projeto](https://github.com/MarianaBarretto/Geracao-Animacoes-Led-5x5/blob/feature/estrutura-codigo/imagem.jpg)

  <h2>Definições de Teclas</h2>
<p>A interação com o sistema é feita através de um teclado matricial com as seguintes definições de teclas:</p>
  <table>
  <thead>
    <tr>
      <th>Tecla</th>
      <th>Função</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>A</td>
      <td>Desliga todos os LEDs.</td>
    </tr>
    <tr>
      <td>B</td>
      <td>Liga todos os LEDs como azul com 100% de intensidade.</td>
    </tr>
    <tr>
      <td>C</td>
      <td>Liga todos os LEDs como vermelho com 80% de intensidade.</td>
    </tr>     
    <tr>
      <td>D</td>
      <td>Liga todos os LEDs como verde com 50% de intensidade.</td>
    </tr> 	
     <tr>
      <td>#</td>
      <td>Aciona LEDs brancos com 20% de intensidade.</td>
      </tr>
	  <tr>
      <td>*</td>
      <td>Sai do modo de execução e habilitar o modo de gravação via software (reboot).</td>
      </tr>
	  </tr>
	  <tr>
      <td>1</td>
      <td>Seta para Cima, Seta para Baixo, Carinha Feliz, Letra T e Letra M</td>
      </tr>
	  </tr>
	  <tr>
      <td>2</td>
      <td>Coração Piscando</td>
      </tr>
	  <tr>
      <td>3</td>
      <td>Ondas Coloridas</td>
      </tr>
    <tr>
      <td>4</td>
      <td>Setas</td>
      </tr>
    <tr>
      <td>5</td>
      <td>Super Nova</td>
      </tr>
    <tr>
      <td>6</td>
      <td>Rosto triste para alegre</td>
      </tr>
    <tr>
      <td>7</td>
      <td>Quadrado Crescente</td>
      </tr>    
    <tr>
    <tr>
      <td>8</td>
      <td>Pong ATARI 1972</td>
      </tr>    
    <tr>
      <td>9</td>
      <td>Circulo Giratório</td>
      </tr>
    
  </tbody>
</table>

<h2>Link do Vídeo do Projeto</h2>

<h3>Wokwi integrado ao VSCode</h3>

<p>Google Drive: https://drive.google.com/file/d/1fgAJERRxqpUFRXN1lQGHSylninKYFOGg</p>
<p>YouTube: https://youtu.be/TtVjypBC0ME</p>

   <h1>Como Executar o Projeto</h1>
        <h2>Clone o Repositório</h2>
    <ol>
        <li>Abra o <strong>Prompt de Comando</strong> ou o terminal de sua preferência.</li>
        <li>Clone o repositório usando o Git:
            <pre><code>git clone https://github.com/seu-usuario/seu-repositorio.git</code></pre>
        </li>
        <li>Entre no diretório do projeto:
            <pre><code>cd seu-repositorio</code></pre>
        </li>
    </ol>    
    <h2>Configuração do Ambiente Local</h2>
    <ol>
        <li>Baixe e instale o <a href="https://cmake.org/download/" target="_blank">CMake</a>.</li>
        <li>Configure o <strong>Pico SDK</strong> seguindo o guia oficial em 
            <a href="https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf" target="_blank">
                Raspberry Pi Pico SDK</a>.
        </li>
        <li>Crie um diretório de construção:
            <pre><code>mkdir build</code></pre>
            <pre><code>cd build</code></pre>
        </li>
        <li>Execute o CMake para gerar os arquivos de construção:
            <pre><code>cmake ..</code></pre>
        </li>
    </ol>
    <h2>Compilar o Projeto</h2>
    <p>Após configurar o ambiente, compile o projeto executando o seguinte comando dentro do diretório <code>build</code>:</p>
    <pre><code>make</code></pre>
    <p>Isso criará o arquivo binário do programa, geralmente no formato <code>.uf2</code>.</p>
   <h2>Testando o Projeto</h2>
    <ul>
        <li>Pressione as teclas no teclado matricial para interagir com o sistema.</li>
        <li>Observe os LEDs para respostas visuais.</li>
        <li>Ouça o som emitido pelo buzzer para ações específicas.</li>
        <li>Verifique a interação com os componentes simulados e depure o código conforme necessário.</li>
    </ul>



