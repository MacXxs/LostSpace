# LostSpace
Small conversational game in the style of Zork made by [Miquel Prieto Moliné](https://github.com/MacXxs) </br>
You can check the repo [here](https://github.com/MacXxs/LostSpace) </br>

## Game Commands
### Interaction commands
- The **LOOK** command prints a description of your surroundings. You can use the **LOOK** command followed by the name of an entity in the room to get a description of that entity alone. </br> Usage: </br>  ```> LOOK``` </br> ```> LOOK entity_name```
- The **INVENTORY** command prints a description of the items in your inventory. </br> Usage: </br> ```> INVENTORY```
- The **OPEN** commmand prints a descriptions of the items contained inside a container. </br> Usage: </br> ```> OPEN container_name```
- The **GRAB** commmand allows you to grab items and store them in you inventory. </br> Usage: </br> ```> GRAB item_name```
- The **DROP** command allows you to drop items from your backpack on the room you're in. </br> Usage: </br> ```> DROP item_name```
- The **USE** command allows you to use items from your backpack or your surroudings. </br> Only recordings and terminals can be used without having them in your inventory. </br> Usage: </br> ```> USE item_name``` </br> ```> USE item_name ON entity_name```
- The **PLACE** command allows you to place an item from your inventory inside a container. </br> Usage: </br> ```> PLACE item_name IN container_name```
- The **CONSUME** command allows you to drink or eat a consumable item. </br> Usage: </br> ```> CONSUME consumable_name```
- The **ATTACK** command allows you attack with your fists an auto-targeted enemy, attack an enemy in particular whith your fists or attack an enemy in particular using a weapon from your inventory. </br> Usage: </br> ```> ATTACK``` </br> ```> ATTACK enemy_name``` </br> ```> ATTACK enemy_name WITH weapon_name```
### Movement Commands
- To walk in a direction just type the direction you wanna move: </br>
```> NORTH``` </br> ```> SOUTH``` </br> ```> EAST``` </br> ```> WEST``` </br> ```> UP``` </br> ```> DOWN```
### Important Information
- Items must be referred by their full name, if an item is labeled "penaut_butter" and you want to get a closer look at it, you must type: </br> ```> LOOK PENAUT_BUTTER```
- It doesn't matter if you use lower or upper cases while typing.
