#Aaron Stromberg
#CS216, version: PA3.0 (after practicum 5)

OBJECTS = Light.o XMLSerializable.o Entity.o Item.o Creature.o Consumable.o Weapon.o Armor.o Potion.o Scroll.o Parser.o Gold.o Ammunition.o DungeonLevel.o RoomTile.o Point.o CreatureFactory.o
HEADERS = Light.h XMLSerializable.h Entity.h Item.h Creature.h Consumable.h Weapon.h Armor.h Potion.h Scroll.h Parser.h Gold.h Ammunition.h DungeonLevel.h RoomTile.h Point.h CreatureFactory.h

all: prog1c1 unit_test

play: $(OBJECTS) main_cl.o
	g++ -std=c++0x $^ -o play -lncurses

unit_test: $(OBJECTS) unit_test.o
	g++ -std=c++0x $^ -o unit_test -lncurses

%.o: %.cpp $(HEADERS)
	g++ -std=c++0x -c $< -o $@

run: play
	./play

itemExec: Menu.o MenuItem.o Field.o Itemerizer.o
	g++ -std=c++0x Menu.o MenuItem.o Field.o Itemerizer.o -o itemerizer -lncurses

itemerizer: itemExec
	./itemerizer

test: unit_test
	./unit_test 20
clean:
	rm -f *.o play unit_test *.save *.save.* 
