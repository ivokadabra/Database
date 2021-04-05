Name: Ivaylo Iliev
Matrikelnummer:1287983


Aufgabe1.2

gedit hello.sql

SELECT 'Hello World!';

\ir hello.sql


Aufgabe1.3 
--------Legen Sie eine beliebige Tabelle mit nur einer Spalte direkt in psqlan(CREATE TABLE ...).-------

CREATE TABLE probe(
nr INT
name VARCHAR(500)
);


-------Zeigen Sie die Struktur dieser Tabelle an (welches Metakommando?).-------
SELECT * FROM probe

---------Erstellen Sie mithilfe eines Editors (z.B. gedit) ein SQL-Script insert.sql, welches SQL-Befehle zum Befüllen derTabelle enthält. FührenSie dieses Script in psqlaus(welches Metakommando?).-------

INSERT INTO probe(
nr 
name 
)VALUE(5,'Anne');

\ir insert.sql

--------Entfernen Sie die Tabelleaus der Datenbank-------
DROP TABLE probe;


Aufgabe 1.4
------Die Tabelle import wird nur vorübergehend für den Datenimport benötigt und sollte nur ausvarcharFeldern bestehen.Wählen Sie in den anderen Tabellen geeignete Datentypen für die verschiedenen Felderund denken Sie an die Definition sinnvoller Integritätsbedingungen.-----

CREATE TABLE import(
nr VARCHAR (500), 
ort VARCHAR(500),
geburtsdatum VARCHAR(500),
name VARCHAR(500) ,
vorname VARCHAR(500) ,
abteilung VARCHAR(500)
abteilungnr VARCHAR(500) ,
gehalt VARCHAR(500) 
);

\copy import from 'dbsnam-utf8.csv'delimiter ','

CREATE TABLE person(
nr INT , 
ort VARCHAR(500),
geburtsdatum DATE,
name VARCHAR(500) ,
vorname VARCHAR(500) ,
abteilungnr VARCHAR(500) ,
gehalt NUMERIC(7,2) 
PRIMARY KEY(nr),
FOREIGN KEY (abteilungnr) REFERENCES abteilung(nr)
);

CREATE TABLE abteilung(
name VARCHAR(500),
nr VARCHAR  (500),
PRIMARY KEY(nr),
FOREIGN KEY (nr) REFERENCES person(abteilungnr)
);
-----------Schreiben Sie ein SQL-Script zum Kopieren der Daten aus der Tabelle importin die Zieltabellen-----------
INSERT INTO person
SELECT DISTINCT CAST(nr AS INT),ort, TO_DATE(geburtsdatum,'DD-MM-YYYY'),name,vorname,abteilungnr,CAST(gehalt AS NUMERIC(7,2) )
FROM import;

INSERT INTO abteilung
SELECT DISTINCT abteilung,abteilungnr
FROM import;

Aufgabe 1.5
-------------Es gibt eine neue Mitarbeiterin namens Berta Griese, die am 04. Februar 1958 geboren wurde. Sie wohnt in Krefeld, arbeitet im Verkauf, verdient 2950 Euro und hat die Personalnr.1001.--------
INSERT INTO person(
nr,
ort,
geburtsdatum,
name,
vorname ,
abteilungnr,
gehalt)
VALUES( 1001,'Krefeld',TO_DATE('04-02-1958','DD-MM-YYYY'),'Griese','Berta','C3',2950);

---------Alle Viersener Mitarbeiter, die in der Produktion arbeiten, werden entlassen------------

DELETE FROM person
WHERE ort='Viersen' AND abteilungnr='C2';

------------Das Gehalt aller Mitarbeiter, die weniger als 3000 € verdienen, wird um 10% erhöht.-----------
UPDATE person
SET gehalt= gehalt+gehalt*10/100
WHERE gehalt<=3000;
-------------Wie viele Mitarbeiter sind 1970 oder später geboren?------------
SELECT COUNT(geburtsdatum) 
FROM person 
WHERE geburtsdatum >=TO_DATE('01-01-1970','DD-MM-YYYY');

-------------Wie heißt die Abteilung, in der UlrichHirzel arbeitet? ------------

SELECT abteilung.name
FROM abteilung
JOIN person
ON abteilung.nr= person.abteilungnr WHERE person.name='Hirzel' AND person.vorname='Ulrich';

------------Was ist das Minimal-, Maximal-und Durchschnittsgehalt je Abteilung? Die Ausgabe soll mit Abteilungsnamenund auf zwei Nachkommastellen gerundet erscheinen------

SELECT abteilung.name,MIN(ROUND(gehalt::numeric,2)),MAX(ROUND(gehalt ::numeric,2)),ROUND(AVG(gehalt) :: numeric,2 ) AS "AVG"
FROM person
JOIN abteilung
ON abteilung.nr= person.abteilungnr
GROUP BY abteilung.nr;




