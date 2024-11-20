const overlay = document.getElementById('overlay');
const celestialBodies = ['sun', 'moon', 'earth'];
const curiosities = {
    sun: ['O Sol contém cerca de 99,86% de toda a massa do Sistema Solar, sendo composto principalmente por hidrogênio e hélio.', 'A energia do Sol é gerada por fusão nuclear no núcleo, onde o hidrogênio é convertido em hélio, liberando energia como luz e calor.', 'A temperatura no núcleo do Sol atinge cerca de 15 milhões de graus Celsius, enquanto sua superfície é relativamente "mais fria," com cerca de 5.500°C.', 'O Sol passa por ciclos de atividade de aproximadamente 11 anos, variando entre máximos e mínimos solares que afetam fenômenos como as auroras e tempestades solares.', 'Estima-se que o Sol está aproximadamente na metade de sua vida, com cerca de 4,6 bilhões de anos, e deve se transformar em uma gigante vermelha antes de finalmente se tornar uma anã branca em cerca de 5 bilhões de anos.'],
    moon: ['Devido à rotação sincronizada, a Lua sempre apresenta a mesma face para a Terra, enquanto o lado oposto é conhecido como "lado oculto da Lua.', 'A Lua não tem uma atmosfera significativa, o que significa que não há proteção contra meteoritos ou variações extremas de temperatura.', 'A hipótese mais aceita é que a Lua se formou após uma colisão entre a Terra primitiva e um corpo do tamanho de Marte chamado Theia, há cerca de 4,5 bilhões de anos.', 'A gravidade lunar é cerca de 1/6 da gravidade da Terra, o que significa que objetos pesam muito menos na Lua.', 'Em 1969, Neil Armstrong e Buzz Aldrin se tornaram os primeiros humanos a caminhar na Lua, durante a missão Apollo 11.'],
    earth: ['O Mauna Loa, no Havaí, é o maior vulcão ativo da Terra, cobrindo cerca de 5.271 km² e atingindo uma altura de mais de 4.000 metros acima do nível do mar.', 'Devido à sua rotação, a Terra é ligeiramente achatada nos polos e mais larga no equador, formando um esferoide oblato.', 'Mais de 80% do oceano da Terra permanece inexplorado, abrigando possíveis espécies desconhecidas e mistérios geológicos.', 'A Terra tem cerca de 4,54 bilhões de anos, baseada em datações de rochas terrestres e meteoritos.', 'O núcleo líquido da Terra gera um campo magnético que protege o planeta dos ventos solares e da radiação cósmica.']
};
const randomInt = () => Math.floor(Math.random() * 5);
const curiositiesElement = document.getElementById('curiosities');
const curiosityDescription = document.getElementById('curiosity');
const namePlanet = document.getElementById('namePlanet');

const socket = io();

socket.on('arduinoData', (data) => {
    console.log(`Data received from server: ${data}`);
    handleArduinoData(data);
});

function handleArduinoData(data) {
    console.log(data)
    if(data == '1'){
        curiositiesElement.style.boxShadow ='0 0 10px 2px #fde24e';
        namePlanet.innerHTML = 'Sol';
        curiosityDescription.style.backgroundColor = '#fde24e';
        curiosityDescription.innerHTML = curiosities.sun[randomInt()];
        overlay.style.display = 'flex';
    }else if('2'){
        curiositiesElement.style.boxShadow ='0 0 10px 2px #2296de';
        namePlanet.innerHTML = 'Terra';
        curiosityDescription.style.backgroundColor = '#2296de';
        curiosityDescription.innerHTML = curiosities.earth[randomInt()];
        overlay.style.display = 'flex';
    }else if('3'){
        curiositiesElement.style.boxShadow ='0 0 10px 2px #d5d5d5';
        namePlanet.innerHTML = 'Lua';
        curiosityDescription.style.backgroundColor = '#d5d5d5';
        curiosityDescription.innerHTML = curiosities.moon[randomInt()];
        overlay.style.display = 'flex';
    }else if('-1'){
        return false;
    }
    return true;
}

celestialBodies.forEach(body => {
    const element = document.getElementById(body);
    element.addEventListener('click', () => {
        if(body === 'sun'){
            curiositiesElement.style.boxShadow ='0 0 10px 2px #fde24e';
            namePlanet.innerHTML = 'Sol';
            curiosityDescription.style.backgroundColor = '#fde24e';
            curiosityDescription.innerHTML = curiosities.sun[randomInt()];
        } else if(body === 'moon'){
            curiositiesElement.style.boxShadow ='0 0 10px 2px #d5d5d5';
            namePlanet.innerHTML = 'Lua';
            curiosityDescription.style.backgroundColor = '#d5d5d5';
            curiosityDescription.innerHTML = curiosities.moon[randomInt()];
        } else {
            curiositiesElement.style.boxShadow ='0 0 10px 2px #2296de';
            namePlanet.innerHTML = 'Terra';
            curiosityDescription.style.backgroundColor = '#2296de';
            curiosityDescription.innerHTML = curiosities.earth[randomInt()];
        }
        overlay.style.display = 'flex';
    });
});




overlay.addEventListener('click', () => {
    overlay.style.display = 'none';
});
