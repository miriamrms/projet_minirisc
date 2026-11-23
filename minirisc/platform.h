/**
 * Definition of a platform object
 */
typedef struct {
    uint32_t *memory;
} platform_t;

/**
 * Type of memory acess
 */
typedef enum {
    PLATFORM_ACCESS_BYTE = 0, //  8 bits
    PLATFORM_ACCESS_HALF = 1, // 16 bits
    PLATFORM_ACCESS_WORD = 3  // 32 bits
} platform_access_type_t;

/**
 * Error codes returned by a platform read/write access. 
 */
typedef enum {
	PLATFORM_OK = 0,                // OK, no error
	PLATFORM_MISALIGNED_ACCESS = 1, // address is not aligned according to the access type
	PLATFORM_ACCESS_FAULT = 2       // trying to access an unpopulated memory region
} platform_error_t;

/**
 * Allocates an initializes a new platform and its memory.
 */
platform_t* platform_new();

/**
 * Cleanup the platform's allocated memories, and the platform object itself.
 */
void platform_free(platform_t *platform);

/**
 * Read one item from the platform.
 * @param platform The platform object
 * @param type     Width of the access
 * @param addr     Address where to read the item
 * @param data     The item is placed in data.
 * @return         0 on success, -1 on error (illegal or misaligned access)
 */
int platform_read(platform_t *plt, platform_access_type_t access_type, uint32_t addr, uint32_t *data);

/**
 * Write one item to the platform.
 * @param platform The platform object
 * @param type     Width of the access
 * @param addr     Address where to write the item
 * @param data     The item to write
 * @return         0 on success, -1 on error (illegal or misaligned access)
 */
int platform_write(platform_t *plt, platform_access_type_t access_type, uint32_t addr, uint32_t data);

/**
 * Read the file named file_name and write its content
 * in the platform's memory.
 * @return 0 on success, -1 on error (cannot open file, etc)
 */
int platform_load_program(platform_t *plt, const char *file_name);