#ifndef FILE_H
#define FILE_H

#include "EEPROMStream.h"
#include <Converter.h>
#include <Logger.h>

#define FILE_HEADER_SIZE 8

/**
 * @brief      Description of file, stored at the start of the file buffer.
 */
class FileHeader
{

public:
	/**
	 * Version of the file.
	 */
	int version;

	/**
	 * Number of bytes, excluding the header.
	 */
	short size;

	/**
	 * Number of records total.
	 */
	short numRecords;

	/**
	 * @brief      Reads header information.
	 *
	 * @param      stream          The stream to read from.
	 * @param[in]  absoluteOffset  The absolute offset of the file.
	 *
	 * @return     True if the header was successfully read.
	 */
	bool read(
		EEPROMStream* stream,
		int absoluteOffset)
	{
		char buffer[FILE_HEADER_SIZE];

		// read file header
		if (FILE_HEADER_SIZE != stream->read(buffer, absoluteOffset, FILE_HEADER_SIZE))
		{
			return false;
		}

		// read in version
		IntUnion intConverter;
		intConverter.charValue[0] = buffer[0];
		intConverter.charValue[1] = buffer[1];
		intConverter.charValue[2] = buffer[2];
		intConverter.charValue[3] = buffer[3];
		version = intConverter.intValue;

		// size
		ShortUnion converter;
		converter.charValue[0] = buffer[4];
		converter.charValue[1] = buffer[5];
		size = converter.shortValue;

		// numrecords
		converter.charValue[0] = buffer[6];
		converter.charValue[1] = buffer[7];
		numRecords = converter.shortValue;

		return true;
	}

	/**
	 * @brief      Writes the header.
	 *
	 * @param      stream  The stream to write with.
	 * @param      absoluteOffset  The absolute offset to write the header.
	 *
	 * @return     True if the header was successfully writtern.
	 */
	bool write(
		EEPROMStream* stream,
		int absoluteOffset)
	{
		// prepare buffer
		char buffer[FILE_HEADER_SIZE];

		IntUnion intConverter;
		intConverter.intValue = version;
		memcpy(buffer, intConverter.charValue, 4);

		ShortUnion shortConverter;
		shortConverter.shortValue = size;
		memcpy(buffer + 4, shortConverter.charValue, 2);

		shortConverter.shortValue = numRecords;
		memcpy(buffer + 6, shortConverter.charValue, 2);

		return stream->write(buffer, absoluteOffset, FILE_HEADER_SIZE);
	}
};

/**
 * @brief      Entry point for adding data to + updating fixed size files.
 */
class File
{
private:

	/**
	 * Logger.
	 */
	static Logger* _logger;

	/**
	 * Stream to read/write with.
	 */
	EEPROMStream* _stream;

	/**
	 * Byte offset into stream.
	 */
	int _offset;

	/**
	 * Buffer used internally to move floats around.
	 */
	char _scratchBuffer[4];

public:

	/**
	 * Header information.
	 */
	FileHeader header;

	/**
	 * @brief      Constructor.
	 */
	File();

	/**
	 * @brief      Loads header into memory. This is for Files that already
	 * exist.
	 *
	 * @param      stream  The stream to read/write from.
	 * @param[in]  offset  The byte offset this file starts at.
	 */
	bool load(EEPROMStream* stream, const int offset);

	/**
	 * @brief      Writes header to disk. This is for new Files.
	 *
	 * @param      stream  The stream to write to.
	 * @param[in]  offset  The byte offset this file starts at.
	 * @param[in]  size    The size, in bytes, of the file.
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool init(EEPROMStream* stream, const int offset, const short size);

	/**
	 * @brief      Retrieves the size of the file.
	 *
	 * @return     Returns the size of the file, in bytes.
	 */
	int size();

	/**
	 * @brief      Flushes any changes to the stream, in case the File decides
	 * to cache.
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool flush();

	/**
	 * @brief      Adds a value to the file.
	 *
	 * @param[in]  value	The float to add to the file.
	 *
	 * @return     Returns true iff the add was successful.
	 */
	bool add(float value);
};

#endif