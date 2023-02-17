#include "esphome.h"
#include <SparkFun_VEML6075_Arduino_Library.h>

class VEML6075Sensor : public PollingComponent {
    public:
        VEML6075 uv;
        Sensor *uva_sensor = new Sensor();
        Sensor *uvb_sensor = new Sensor();
        Sensor *uvi_sensor = new Sensor();

    VEML6075Sensor(uint32_t update_interval) : PollingComponent(update_interval) { }

    float get_setup_priority() const override { return esphome::setup_priority::BUS; }

    void setup() override {
        // This will be called by App.setup()
        Wire.begin();
        if ( uv.begin() == false ){
            Serial.println("Unable to communicate with VEML6075");
        }
        uv.setIntegrationTime(VEML6075::IT_100MS);
        uv.setHighDynamic(VEML6075::DYNAMIC_NORMAL);
    }

    void update() override {
        // This will be called by App.loop()
        float uva = uv.uva();
        uva_sensor->publish_state(uva);

        float uvb = uv.uvb();
        uvb_sensor->publish_state(uvb);

        float uvi = uv.index();
        uvi_sensor->publish_state(uvi);

    }
};