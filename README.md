# KTH Examensarbete
Det här projektet handlar om att skapa en modell skriven i C för en väderapplikation som är avsedd för användning med SMHI-data. Modellkoden innehåller getter- och setter-funktioner samt en array som möjliggör hämtning av data och tillägg av nya data. Dessutom inkluderar projektet två funktioner som liknar en konstruktor och använder pekare för att skapa en objektorienterad struktur. Modellkoden används i Android, iOS och HTML5. 

I Android används Java Native Interface (JNI) tillsammans med programmeringsspråket Kotlin för att hantera modellkoden. Utligare Ytligare verktyg för Android så används Jetpack Compose som användargränssnitt och Retrofit som tar hand om databasen och HTTP anrop. 

På iOS använder vi Swift och inbyggd interoperabilitet i Swift för att integrera och använda modellkoden som är skriven i C. Ytligare verktyg så används Swift inbyggda verkyg för att hantera HTTP anrop samt Core data för att hantera databasen.

Dessutom, för `HTML5`, använder vi `WebAssembly` för att köra modellkoden. Ytligare verktyg så används JavaScript inbyggda HTTP anrop samt IndexedDB för att ta hand om databasen.


**OBS:** Det finns två applikationer på Android, iOS och HTML5 där en använder modellkoden skriven i C och en utan.

**Återanvändning av kod på Android, iOS och HTML5**

Kom igång manual finns på projekt som har modellkod skriven i C.
Medans resten av applikationer kan köras direkt utan några problem.


## Author
Emre Demirel [@98emre](https://github.com/98emre)

Shifat Chowdhury [@shch99](https://github.com/98emre)
