#include <catch.hpp>

#include <database_manager.h>
#include <memory_stream.h>
#include <standard_clock.hpp>
#include <function_pointer_log_target.h>

#include "sensor_manager.h"
#include "sensor.h"
#include "sensor_config.h"

class DummySensor : public Sensor
{
public:
	int pollCount;

	~DummySensor()
	{
		//
	}

	bool poll(const float* values) override
	{
		pollCount += 1;

		return true;
	}
};

void log(const char* message)
{
	INFO(message);
}

TEST_CASE("SensorManager", "[SensorManager]")
{
	FunctionPointerLogTarget* logger = new FunctionPointerLogTarget(log);
	Log::addTarget(logger);

	// setup
	AvrClock* clock = new StandardClock();
	MemoryStream* stream = new MemoryStream(4096);
	DatabaseManager* data = new DatabaseManager(clock, stream);
	
	DatabaseManagerConfig config;
	REQUIRE(data->init(config));

	SensorManager* sensors = new SensorManager(data);

	{
		DummySensor* dummy = new DummySensor();
		SensorConfig sensorConfig("DummySE", 1024);
		sensorConfig.pollIntervalMs = 10;

		dummy->init(sensorConfig);

		REQUIRE(sensors->add(dummy));

		sensors->update(1);

		REQUIRE(dummy->pollCount == 0);

		sensors->update(9);

		REQUIRE(dummy->pollCount == 1);

		sensors->update(100);

		REQUIRE(dummy->pollCount == 2);

		REQUIRE(sensors->remove(dummy));

		sensors->update(100);

		REQUIRE(dummy->pollCount == 2);

		delete dummy;
	}

	// teardown
	delete sensors;
	delete data;
	delete stream;
	delete clock;
	delete logger;
}