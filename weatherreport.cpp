#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };

    // Existing stub
    class SensorStub : public IWeatherSensor {
        int Humidity() const override {
            return 72;
        }

        int Precipitation() const override {
            return 70;
        }

        double TemperatureInC() const override {
            return 26;
        }

        int WindSpeedKMPH() const override {
            return 52;
        }
    };

    // New stub added to expose the bug (high precip + high wind)
    class StormyStub : public IWeatherSensor {
        int Humidity() const override {
            return 90;
        }

        int Precipitation() const override {
            return 80; // high precipitation
        }

        double TemperatureInC() const override {
            return 30; // hot enough
        }

        int WindSpeedKMPH() const override {
            return 90; // stormy wind
        }
    };

    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
    void TestRainy()
    {
        SensorStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        assert(report.find("rain") != string::npos);
    }

    void TestHighPrecipitation()
    {
        SensorStub sensor;
        string report = Report(sensor);
        assert(report.length() > 0); // weak test
    }

    // New test to expose bug
    void TestStormCondition()
    {
        StormyStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        // This should fail because bug prevents correct storm report
        assert(report.find("Stormy") != string::npos);
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    WeatherSpace::TestStormCondition(); // Run the new test
    cout << "All is well (maybe)\n";
}
