#include "GuiItemBuilder.h"

GuiItem* GuiItemBuilder::buildBars() {
	GuiItem* bars = new Picture("bars.png", vec3(0.0f, aspect * 70.0f / 611.0f - 1.0f, 0.0f), 0.0f, 0.0f, 0.0f,
		vec3(2.0f, 2.0f * aspect * 70.0f / 611.0f, 1.0f));

	return bars;
}

GuiItem* GuiItemBuilder::buildInventory() {
	constexpr float maxHeight = 2.0f;
	constexpr float maxWidth = 2.0f;

	int columns = 9;
	int rows = 14;
	float height = maxHeight;
	float width = height * (float)columns / (float)rows / aspect;
	vec3 position = vec3(1.0f - width / 2, 0.0f, 0.0f);
	vec3 scale = vec3(width, height, 1.0f);
	GuiItem* inventory = new Frame(columns, rows, position, 0.0f, 0.0f, 0.0f, scale);

	columns = 5;
	rows = 4;
	GuiItem* slots = new SlotArray(columns, rows, vec3(position.x, position.y + scale.y * (118.0f / 336.0f - 0.5f), position.z),
		0.0f, 0.0f, 0.0f, vec3(200.0f / 216.0f * scale.x, 160.0f / 336.0f * scale.y, 1.0f));

	GuiItem* head = new Slot(vec3(position.x, position.y + scale.y * (0.5f - 28.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	GuiItem* body = new Slot(vec3(position.x, position.y + scale.y * (0.5f - 70.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	GuiItem* weapon = new Slot(vec3(position.x - scale.x * 42.0f / 216.0f, position.y + scale.y * (0.5f - 70.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	GuiItem* shield = new Slot(vec3(position.x + scale.x * 42.0f / 216.0f, position.y + scale.y * (0.5f - 70.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	GuiItem* pants = new Slot(vec3(position.x, position.y + scale.y * (0.5f - 112.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	GuiItem* gloves = new Slot(vec3(position.x - scale.x * 42.0f / 216.0f, position.y + scale.y * (0.5f - 112.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	GuiItem* boots = new Slot(vec3(position.x + scale.x * 42.0f / 216.0f, position.y + scale.y * (0.5f - 112.0f / 336.0f), position.z),
		0.0f, 0.0f, 0.0f, vec3(40.0f / 216.0f * scale.x, 40.0f / 336.0f * scale.y, 1.0f));

	columns = 7;
	GuiItem* zen = new TextField(columns, vec3(position.x + scale.x * (0.5f - (8.0f + (float)columns * 24.0f / 2) / 216.0f), position.y + scale.y * (20.0f / 336.0f - 0.5f), position.z),
		0.0f, 0.0f, 0.0f, vec3(24.0f * columns / 216.0f * scale.x, 24.0f / 336.0f * scale.y, 1.0f));

	GuiItem* coin = new Picture("coin.png",
		vec3(position.x + scale.x * ((208.0f - 24.0f * columns) / 216.0f / 2 - 0.5f), position.y + scale.y * (20.0f / 336.0f - 0.5f), position.z),
		0.0f, 0.0f, 0.0f, vec3(18.0f / 216.0f * scale.x, 18.0f / 336.0f * scale.y, 1.0f));

	inventory->addChildren({ slots, head, body, weapon, shield, pants, gloves, boots, zen, coin });

	return inventory;
}