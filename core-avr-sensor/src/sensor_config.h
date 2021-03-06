#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

#include <stdlib.h>
#include <database.h>
#include <pin_configuration.h>

// Length of id field.
#define kSensorIdLen 8

// One week of data, polled every 10 secs.
// Assuming AT45DB321E chip, ~ 4MB this means ~8 sensors.
#define kSensorDbLen 483840

/**
 * @brief      Configuration for sensors.
 */
class SensorConfig
{
public:
	/**
	 * Unique identifier for this sensor. This should remain the same across
	 * sessions.
	 */
	char identifier[kSensorIdLen];

	/**
	 * Number of milliseconds we should wait between polls.
	 */
	int pollIntervalMs;

	/**
	 * Size of database in bytes.
	 */
	int dbSize;

	/**
	 * Number of values this sensor returns.
	 */
	int numValues;

	/**
	 * Contains pin information.
	 */
	PinConfiguration pins;

	/**
	 * @brief      Constructor. Requires a unique identifier for this sensor.
	 * Should be constant across sessions.
	 *
	 * @param[in]  id    The unique identifier.
	 * @param[in]  databaseSize   Size of the database in bytes.
	 */
	SensorConfig(
		const char ident[kSensorIdLen],
		int databaseSize,
		int numValues = 1)
	:
		dbSize(databaseSize),
		numValues(numValues)
	{
		memcpy(identifier, ident, kSensorIdLen);
	}

	/**
	 * @brief      Destructor.
	 */
	virtual ~SensorConfig()
	{
		//
	}
};

#endif