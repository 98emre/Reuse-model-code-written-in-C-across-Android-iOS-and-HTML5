# Kom igång med HTML5 applikation som har modellkod skriven i programspråket C.

Krav: Microsoft Visual Studio Code och VS Code Extension Live Server av Ritwick Dey.

1. För att köra HTML5-applikation med modellkod skriven i C behöver du först installera Live Server, som finns tillgängligt som extension på VS Code.
<img width="454" alt="bild" src="https://github.com/shch99/KTHExamensarbete2023/assets/131250228/838c4105-5b8d-4fe6-8f98-864dd036770e">

2. Efter installationen går du tillbaka till projektmappen och klickar på HTML5-filen. För att starta Live Server klickar du på knappen "Go Live" som finns längst ner till höger i Visual Studio Code.
<img width="454" alt="bild" src="https://github.com/shch99/KTHExamensarbete2023/assets/131250228/793342d0-bbdd-48a3-9b84-9ddb8c7b3753">
</br>3. Därefter är du redo att köra applikationen.


## För utvecklare som vill forsätta vidareutveckla koden
</br>Krav: Emscripten, VS Code


### Installation av Emscripten Compiler(emsdk)

1. Följ den officiella dokumentationen för att installera Emscripten-compilern om du inte redan har den installerad: [Länk till Emscripten-dokumentation](https://emscripten.org/docs/getting_started/downloads.html)

### Kompilera C-kod till WebAssembly

2. Öppna terminalen och navigera till projektmappen.

3. När du har hittat mappen i terminalen, verifiera att `emsdk` är aktiverat genom att köra kommandot `emcc -v`.

4. Kompilera C-koden till WebAssembly med följande kommando:emcc Abstract.c Model.c -o Model.js -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

5. Efter kompileringen kommer två filer att skapas. Den första filen innehåller ren WASM-kod och den andra filen innehåller JS-Glue-koden. Glue-koden möjliggör anrop till metoder i JavaScript från C via WASM.

6. Följ instruktionerna i föregående dokumentationen hur man startar HTML5-applikationen.

## Author
Emre Demirel [@98emre](https://github.com/98emre)

Shifat Chowdhury [@shch99](https://github.com/98emre)
