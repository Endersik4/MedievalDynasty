# MedievalDynasty
 making UI from Medieval Dynasty with COOP (inventory, knowledge, perks etc)

Video: <a href="https://youtu.be/rmvkUA3AKrw"> Medieval Dynasty UI (09.07.2024) </a> <br/>
Below are screenshots of the current progress of the Medieval Dynasty UI
<br/><br/>
<h2>Current Features (14.07.2024):</h2>
<h3>Interaction Menu</h3>
<ul>
	<li>A menu that holds all submenus (inventory, skills, map, etc.)</li>
	<li>Spawns a submenu widget when a SubMenuEntry is clicked</li>
	<li>Can immediately open a specified menu (e.g., when the player presses "M," the map menu opens)</li>
</ul>
<h3>Inventory</h3>
<ul>
	<li>Displays all items in the player's inventory with visible icons, names, amounts, durability, weight, and price</li>
	<li>Players can select a category to display only items of that type (e.g., Tools category)</li>
	<li>Category names are shown as text with decorative elements</li>
	<li>Items can be sorted by name, price, weight, or amount</li>
	<li>Items can be clicked, changing the font and background color, and displaying detailed information such as description, storage type, and durability</li>
	<li>Shows the total weight of all items; if it exceeds the player's carrying capacity, the weight text font color changes</li>
	<li>Displays current money, with the amount taken from items of type "Money"</li>
	<li>Items can be dragged; the dragging item widget spawns from the item icon location and moves to the cursor position</li>
	<li>Dragging starts when the player moves the mouse slightly while pressing</li>
	<li>If there are no items in the inventory/category, the text "No Items Found" is displayed</li>
	<li><strong>Player's Equipment</strong></li>
	<ul>
		<li>Shows the player's nickname and age</li>
		<li>Renders the player model in real-time as a render target</li>
		<li>Players can equip items of the appropriate type (e.g., an item with the type "Leg Wear" can be equipped in the "Leg Wear" slot)</li>
		<li>When an item with an equipment type is selected, the corresponding equipment slot is highlighted</li>
		<li>If a slot is occupied, the button is blocked (can't be hovered or clicked), but equipment can still be changed</li>
	</ul>
	<li><strong>Quick Select</strong></li>
	<ul>
		<li>Items can be dragged to the Quick Select Slot</li>
		<li>Items can be dragged from the Quick Select Slot, spawning the dragging item widget from the item icon location</li>
		<li>Only items of the appropriate type can be dragged to the Quick Select Slot (e.g., Tools)</li>
	</ul>
	<li><strong>Player's Status</strong></li>
	<ul>
		<li>Displays all player statuses such as Health, Food, Water, Poison, Temperature, etc.</li>
		<li>For temperature, an additional image acts as a pointer to show the current temperature instead of a progress bar</li>
		<li>When the player hovers over a status, the status name is displayed with a background image at the cursor location</li>
	</ul>
	<li>Player's equipment slots, Quick Select slots, and player's status are implemented as entries in Tile/List view, allowing easy addition of more entries</li>
	
</ul>
<h3>Map</h3>
<ul>
	<li>Displays world information from the game instance such as current temperature, day, season, year, king, and relations (rich text block with images)</li>
	<li>Waypoints can be sorted (e.g., "People" shows different waypoints than "Houses," though currently sorting is only visual)</li>
	<li>Waypoints are sourced from a data table and sorted into categories</li>
	<li>The map can be moved around with clamped location</li>
	<li>The map can be zoomed in/out at the cursor position</li>
</ul>
<h3>Knowledge</h3>
<i>(I'm planning to rework this section as the current implementation is not ideal)</i><br/>
<ul>
	<li>Categories with different knowledge topics</li>
	<li>Drop-down menus displaying the name and the number of entries in each menu</li>
	<li>When a DropDownMenuButton is pressed, all entries from the clicked drop-down menu are displayed and the menu is highlighted</li>
	<li>Pressing next to a DropDownMenuButton will only highlight the drop-down menu</li>
	<li>When a spawned entry from a drop-down menu is pressed, detailed knowledge information is displayed</li>
	<li>Detailed knowledge information includes: name of knowledge, category icon, knowledge description with a scroll bar for long text, and a video if added</li>
</ul>

![ScreenShot00000](https://github.com/Endersik4/MedievalDynasty/assets/131354098/f822154e-cafa-4f08-b205-8b0107bd1ec6)
![ScreenShot00010](https://github.com/user-attachments/assets/6d68a03d-1d8a-4065-ad45-c3d494a5f14e)
![ScreenShot00003](https://github.com/Endersik4/MedievalDynasty/assets/131354098/b575b7e0-d5d8-4b87-ae07-15e43a729264)
![ScreenShot00004](https://github.com/Endersik4/MedievalDynasty/assets/131354098/1c381fc5-a4f4-48b6-874f-0d0d5789dc8e)
![ScreenShot00005](https://github.com/Endersik4/MedievalDynasty/assets/131354098/be113ee4-6790-48d5-acbd-35cccfa41566)
![ScreenShot00006](https://github.com/Endersik4/MedievalDynasty/assets/131354098/6fe26ba4-b817-457c-bd43-04ebad5274c1)
![ScreenShot00008](https://github.com/user-attachments/assets/4acb1b1e-fa2d-446a-84a6-dcb770179781)
![ScreenShot00011](https://github.com/user-attachments/assets/1e132bfd-a9c6-47b3-be0b-1b979cc3129e)


