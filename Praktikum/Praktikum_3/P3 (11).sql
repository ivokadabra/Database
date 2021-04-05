Aufgabe 1:
--------------------------------------------------
create function current_gehalt()
returns trigger as '
declare 
   gehalt_begr Numeric(8,1);
   datum_begr DATE;
   temp INT;
begin
 
  select avg(gehalt) into gehalt_begr from person join abteilung on abteilung.anr=new.abteilungnr and abteilung.anr=person.abteilungnr;
  RAISE NOTICE ''GEHALT nach select is  %'',gehalt_begr;
 -- RAISE NOTICE ''new.pnr is % '',new.abteilungnr;

  if not found then
       RAISE NOTICE ''NOT FOUND %'',gehalt_begr;
  end if;
  if gehalt_begr IS NULL THEN
        RAISE NOTICE ''GEHALT is  %'',gehalt_begr;
        --insert into gehaltshistorie values(NEW.pnr,NEW.gehalt,NEW.gueltigAb,current_date,current_user,TG_OP);
        return new;
  end if;

if(TG_OP =''UPDATE'')then
   RAISE NOTICE ''IN UPDATE %'',gehalt_begr;
    RAISE NOTICE ''IN UPDATE old % and new % old.gehalt % new gehalt % old.gueltigAb % new.gueltigAb %'',old.pnr,new.pnr,old.gehalt,new.gehalt,old.gueltigAb,new.gueltigAb;
   if(old.gehalt<new.gehalt and old.gueltigAb <=new.gueltigAb and new.gehalt<=gehalt_begr*0.5 +gehalt_begr )then
        RAISE NOTICE ''IN SECOND IF %'',gehalt_begr;
          if(new.gehalt>old.gehalt * 1.2)then
                 RAISE NOTICE ''120 Prozent is %'',old.gehalt * 1.2;
                --update gehaltshistorie  set gehalt=old.gehalt * 1.2,gueltigAb=NEW.gueltigAb,aenderungzeitpunkt= current_date,user_name=current_user where pnr=old.pnr;
                   insert into gehaltshistorie values(old.pnr,old.gehalt,old.gueltigAb,current_date,current_user,TG_OP);
                   new.gehalt=old.gehalt * 1.2;
                return new;
          end if;
          --update gehaltshistorie  set gehalt=new.gehalt,gueltigAb=NEW.gueltigAb,aenderungzeitpunkt= current_date,user_name=current_user where pnr=old.pnr;
          insert into gehaltshistorie values(old.pnr,old.gehalt,old.gueltigAb,current_date,current_user,TG_OP);
          RAISE NOTICE ''old.pnr is % '',old.pnr;
       return new;
    
      end if ;
end if ;

if(TG_OP =''INSERT'')then
     RAISE NOTICE ''IN INSERT %'',gehalt_begr;
     if(gehalt_begr<new.gehalt and new.gehalt<=gehalt_begr*0.5 +gehalt_begr)then
        RAISE NOTICE ''IN SECOND IF % and second is % and aktion is %'',gehalt_begr,gehalt_begr*0.5 +gehalt_begr,TG_OP;
       --insert into gehaltshistorie values(NEW.pnr,NEW.gehalt,NEW.gueltigAb,current_date,current_user,TG_OP );
       return new;
     end if ;
end if;





 

RAISE EXCEPTION ''Hier müssen jeweils zwei HOCHKOMATAA stehen % % % % %'',old.pnr,new.pnr,old.gehalt,new.gehalt,gehalt_begr;
end;
'language 'plpgsql';
 


create trigger t_current_gehalt
 before insert or update on person
 for each row execute procedure  current_gehalt();


---------------------------------------------------

CREATE TABLE gehaltshistorie(
pnr SERIAL,
gehalt Numeric(8,2),
gueltigAb DATE,
aenderungzeitpunkt DATE,
user_name VARCHAR(10),
aktion VARCHAR(20)
);


--------------------------------------------------
CREATE TABLE person(
pnr INT,
name VARCHAR(30),
vorname VARCHAR(30),
abteilungnr INT,
gehalt Numeric(8,2),
gueltigAb DATE,
PRIMARY KEY(pnr),
CONSTRAINT fk_customer FOREIGN KEY(abteilungnr) REFERENCES abteilung(anr)
);
--------------------------------------------------
CREATE TABLE abteilung(
anr INT,
name VARCHAR(30),
PRIMARY KEY(anr)
);
--------------------------------------------------
Aufgabe 2: 
--------------------------------------------------

SELECT a.anr, a.name, count(g.*)
FROM abteilung a

LEFT JOIN person p
ON p.abteilungnr = a.anr

LEFT JOIN gehaltshistorie g
ON g.pnr = p.pnr

GROUP BY a.anr;
--------------------------------------------------
CREATE VIEW alleGehaelter(pnr,gehalt,gueltigAbb) AS SELECT pnr,gehalt,gueltigAb FROM person UNION SELECT pnr,gehalt ,gueltigAb  FROM gehaltshistorie ORDER BY pnr;
--------------------------------------------------
SELECT * FROM alleGehaelter WHERE pnr='1' AND gueltigAbb='2019-01-01';


