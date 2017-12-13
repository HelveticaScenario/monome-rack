#include "monomemodulebase.hpp"
#include "rack.hpp"

#include <unordered_set>

using namespace rack;

#define GRID_MAX_SIZE 256

struct MonomeGrid : Module
{
    MonomeModuleBase* connectedModule = NULL;
    MonomeDevice device;

    uint8_t ledBuffer[GRID_MAX_SIZE];
    bool pressedState[GRID_MAX_SIZE];

    MonomeGrid(unsigned w, unsigned h);

    void step() override;

    json_t* toJson() override;
    void fromJson(json_t* rootJ) override;

    void updateQuadrant(int x, int y, uint8_t* leds);
    void clearAll();
};

struct MonomeKey;

typedef enum {
    MonoRed,
    VariYellow
} GridTheme;

struct MonomeGridWidget : ModuleWidget
{
    MonomeGridWidget(unsigned w, unsigned h, unsigned model);

    json_t* toJson() override;
    void fromJson(json_t* rootJ) override;
    Menu* createContextMenu() override;
    void onDragEnter(EventDragEnter& e) override;
    void onMouseDown(EventMouseDown& e) override;
    void randomize() override;

    void clearHeldKeys();

protected:
    friend struct MonomeKey;
    bool isDraggingKeys;
    std::unordered_set<MonomeKey*> keysTouchedThisDrag;

    Vec margins;
    GridTheme theme;
};

template <unsigned width, unsigned height, unsigned modelIndex>
struct MonomeGridWidgetTemplate : MonomeGridWidget
{
    MonomeGridWidgetTemplate()
        : MonomeGridWidget(width, height, modelIndex)
    {
    }
};
