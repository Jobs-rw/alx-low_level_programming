#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * compare_strings - Compare two strings up to maxBytes
 * @string1: First string to be compared
 * @string2: Second string to be compared
 * @maxBytes: Maximum bytes to compare
 * Return: Difference between the two strings, 0 if they are the same
 */
int compare_strings(const char *string1, const char *string2, size_t maxBytes)
{
	for (; maxBytes && *string1 && *string2; --maxBytes, ++string1, ++string2)
		if (*string1 != *string2)
			return (*string1 - *string2);
	if (maxBytes)
	{
		if (*string1)
			return (1);
		if (*string2)
			return (-1);
	}
	return (0);
}

/**
 * close_file_descriptor - Close a file descriptor
 * @fileDescriptor: File descriptor to close
 */
void close_file_descriptor(int fileDescriptor)
{
	if (close(fileDescriptor) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't close fd\n", 22);
	exit(98);
}

/**
 * read_from_file - Read from a file
 * @fileDescriptor: File descriptor to read from
 * @buffer: Buffer to store the data
 * @numBytes: Number of bytes to read
 */
void read_from_file(int fileDescriptor, char *buffer, size_t numBytes)
{
	if (read(fileDescriptor, buffer, numBytes) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't read from file\n", 28);
	close_file_descriptor(fileDescriptor);
	exit(98);
}

/**
 * print_elf_magic - Print the magic number from the ELF header
 * @elfHeader: The ELF header
 */
void print_elf_magic(const unsigned char *elfHeader)
{
	unsigned int i;

	if (compare_strings((const char *)elfHeader, ELFMAG, 4))
	{
		write(STDERR_FILENO, "Error: Not an ELF file\n", 23);
		exit(98);
	}
	printf("ELF Header:\n  Magic:   ");
	for (i = 0; i < 16; ++i)
		printf("%02x%c", elfHeader[i], i < 15 ? ' ' : '\n');
}

/**
 * print_elf_class - Print the class from the ELF header
 * @elfHeader: The ELF header
 * Return: 64 if ELF64, 32 if ELF32
 */
size_t print_elf_class(const unsigned char *elfHeader)
{
	printf("  %-34s ", "Class:");
	if (elfHeader[EI_CLASS] == ELFCLASS64)
	{
		printf("ELF64\n");
		return (64);
	}
	if (elfHeader[EI_CLASS] == ELFCLASS32)
	{
		printf("ELF32\n");
		return (32);
	}
	printf("<unknown: %x>\n", elfHeader[EI_CLASS]);
	return (32);
}

/**
 * print_elf_data - Print the data from the ELF header
 * @elfHeader: The ELF header
 * Return: 1 if big endian, 0 if little endian
 */
int print_elf_data(const unsigned char *elfHeader)
{
	printf("  %-34s ", "Data:");
	if (elfHeader[EI_DATA] == ELFDATA2MSB)
	{
		printf("2's complement, big endian\n");
		return (1);
	}
	if (elfHeader[EI_DATA] == ELFDATA2LSB)
	{
		printf("2's complement, little endian\n");
		return (0);
	}
	printf("Invalid data encoding\n");
	return (0);
}
/**
 * print_elf_version - Print the version from the ELF header
 * @elfHeader: The ELF header
 */
void print_elf_version(const unsigned char *elfHeader)
{
	printf("  %-34s %u", "Version:", elfHeader[EI_VERSION]);
	if (elfHeader[EI_VERSION] == EV_CURRENT)
		printf(" (current)\n");
	else
		printf("\n");
}

/**
 * print_elf_osabi - Print the OS/ABI from the ELF header
 * @elfHeader: The ELF header
 */
void print_elf_osabi(const unsigned char *elfHeader)
{
	const char *os_table[19] = {
		"UNIX - System V", "UNIX - HP-UX", "UNIX - NetBSD", "UNIX - GNU",
		"<unknown: 4>", "<unknown: 5>", "UNIX - Solaris", "UNIX - AIX",
		"UNIX - IRIX", "UNIX - FreeBSD", "UNIX - Tru64", "Novell - Modesto",
		"UNIX - OpenBSD", "VMS - OpenVMS", "HP - Non-Stop Kernel", "AROS",
		"FenixOS", "Nuxi CloudABI", "Stratus Technologies OpenVOS"
	};
	printf("  %-34s ", "OS/ABI:");
	if (elfHeader[EI_OSABI] < 19)
		printf("%s\n", os_table[(unsigned int)elfHeader[EI_OSABI]]);
	else
		printf("<unknown: %x>\n", elfHeader[EI_OSABI]);
}

/**
 * print_elf_abi_version - Print the ABI version from the ELF header
 * @elfHeader: The ELF header
 */
void print_elf_abi_version(const unsigned char *elfHeader)
{
	printf("  %-34s %u\n", "ABI Version:", elfHeader[EI_ABIVERSION]);
}

/**
 * print_elf_type - Print the type from the ELF header
 * @elfHeader: The ELF header
 * @bigEndian: 1 if big endian, 0 if little endian
 */
void print_elf_type(const unsigned char *elfHeader, int bigEndian)
{
	char *type_table[5] = {
		"NONE (No file type)", "REL (Relocatable file)", "EXEC (Executable file)",
		"DYN (Shared object file)", "CORE (Core file)"
	};
	unsigned int elfType;

	printf("  %-34s ", "Type:");
	if (bigEndian)
		elfType = 0x100 * elfHeader[16] + elfHeader[17];
	else
		elfType = 0x100 * elfHeader[17] + elfHeader[16];
	if (elfType < 5)
		printf("%s\n", type_table[elfType]);
	else if (elfType >= ET_LOOS && elfType <= ET_HIOS)
		printf("OS Specific: (%4x)\n", elfType);
	else if (elfType >= ET_LOPROC && elfType <= ET_HIPROC)
		printf("Processor Specific: (%4x)\n", elfType);
	else
		printf("<unknown: %x>\n", elfType);
}

/**
 * print_elf_entry_point - Print the entry point from the ELF header
 * @entryPointBuffer: The entry point
 * @bitMode: The bit mode
 * @bigEndian: 1 if big endian, 0 if little endian
 */
void print_elf_entry_point(const unsigned char *entryPointBuffer,
size_t bitMode, int bigEndian)
{
	int addressSize = bitMode / 8;

	printf("  %-34s 0x", "Entry point address:");
	if (bigEndian)
	{
		while (addressSize && !*(entryPointBuffer))
			--addressSize, ++entryPointBuffer;
		printf("%x", *entryPointBuffer & 0xff);
		while (--addressSize > 0)
			printf("%02x", *(++entryPointBuffer) & 0xff);
	}
	else
	{
		entryPointBuffer += addressSize;
		while (addressSize && !*(--entryPointBuffer))
			--addressSize;
		printf("%x", *entryPointBuffer & 0xff);
		while (--addressSize > 0)
			printf("%02x", *(--entryPointBuffer) & 0xff);
	}
	printf("\n");
}

/**
 * main - Main function
 * @argCount: Number of arguments
 * @argValues: Array of arguments
 * Return: 0 on success, 98 on error
 */
int main(int argCount, const char *argValues[])
{
	unsigned char elfHeaderBuffer[18];
	unsigned int bitMode;
	int bigEndian;
	int fileDescriptor;

	if (argCount != 2)
	{
		write(STDERR_FILENO, "Usage: elf_header elf_filename\n", 31);
		exit(98);
	}
	fileDescriptor = open(argValues[1], O_RDONLY);
	if (fileDescriptor == -1)
	{
		write(STDERR_FILENO, "Error: Can't read from file\n", 28);
		exit(98);
	}
	read_from_file(fileDescriptor, (char *)elfHeaderBuffer, 18);
	print_elf_magic(elfHeaderBuffer);
	bitMode = print_elf_class(elfHeaderBuffer);
	bigEndian = print_elf_data(elfHeaderBuffer);
	print_elf_version(elfHeaderBuffer);
	print_elf_osabi(elfHeaderBuffer);
	print_elf_abi_version(elfHeaderBuffer);
	print_elf_type(elfHeaderBuffer, bigEndian);
	lseek(fileDescriptor, 24, SEEK_SET);
	read_from_file(fileDescriptor, (char *)elfHeaderBuffer, bitMode / 8);
	print_elf_entry_point(elfHeaderBuffer, bitMode, bigEndian);
	close_file_descriptor(fileDescriptor);
	return (0);
}
