/*****************************************************************************
Basic typedefs:
*****************************************************************************/

/**
Client API:
Signed twos-complement 8-bit type. Typically defined as signed char.
*/
typedef signed... sox_int8_t;

/**
Client API:
Unsigned 8-bit type. Typically defined as unsigned char.
*/
typedef unsigned... sox_uint8_t;

/**
Client API:
Signed twos-complement 16-bit type. Typically defined as short.
*/
typedef short... sox_int16_t;

/**
Client API:
Unsigned 16-bit type. Typically defined as unsigned short.
*/
typedef unsigned... sox_uint16_t;

/**
Client API:
Signed twos-complement 32-bit type. Typically defined as int.
*/
typedef int... sox_int32_t;

/**
Client API:
Unsigned 32-bit type. Typically defined as unsigned int.
*/
typedef unsigned... sox_uint32_t;

/**
Client API:
Signed twos-complement 64-bit type. Typically defined as long or long long.
*/
typedef int... sox_int64_t;

/**
Client API:
Unsigned 64-bit type. Typically defined as unsigned long or unsigned long long.
*/
typedef int sox_uint64_t;

/**
Client API:
Alias for sox_int32_t (beware of the extra byte).
*/
typedef int... sox_int24_t;

/**
Client API:
Alias for sox_uint32_t (beware of the extra byte).
*/
typedef unsigned... sox_uint24_t;

/**
Client API:
Native SoX audio sample type (alias for sox_int32_t).
*/
typedef int... sox_sample_t;


/**
Client API:
Samples per second is stored as a double.
*/
typedef double sox_rate_t;

/**
Client API:
File's metadata, access via sox_*_comments functions.
*/
typedef char * * sox_comments_t;

/*****************************************************************************
Enumerations:
*****************************************************************************/

/**
Client API:
Boolean type, assignment (but not necessarily binary) compatible with C++ bool.
*/
typedef enum sox_bool {
    sox_false, /**< False = 0. */
    sox_true,   /**< True = 1. */
    ...
} sox_bool;

/**
Client API:
no, yes, or default (default usually implies some kind of auto-detect logic).
*/
typedef enum sox_option_t {
    sox_option_no,      /**< Option specified as no = 0. */
    sox_option_yes,     /**< Option specified as yes = 1. */
    sox_option_default  /**< Option unspecified = 2. */
} sox_option_t;

/**
Client API:
The libSoX-specific error codes.
libSoX functions may return these codes or others that map from errno codes.
*/
enum sox_error_t {
  SOX_SUCCESS = 0,     /**< Function succeeded = 0 */
  SOX_EOF = -1,        /**< End Of File or other error = -1 */
  SOX_EHDR = 2000,     /**< Invalid Audio Header = 2000 */
  SOX_EFMT,            /**< Unsupported data format = 2001 */
  SOX_ENOMEM,          /**< Can't alloc memory = 2002 */
  SOX_EPERM,           /**< Operation not permitted = 2003 */
  SOX_ENOTSUP,         /**< Operation not supported = 2004 */
  SOX_EINVAL           /**< Invalid argument = 2005 */
};


/**
Client API:
Format of sample data.
*/
typedef enum sox_encoding_t {
  SOX_ENCODING_UNKNOWN   , /**< encoding has not yet been determined */

  SOX_ENCODING_SIGN2     , /**< signed linear 2's comp: Mac */
  SOX_ENCODING_UNSIGNED  , /**< unsigned linear: Sound Blaster */
  SOX_ENCODING_FLOAT     , /**< floating point (binary format) */
  SOX_ENCODING_FLOAT_TEXT, /**< floating point (text format) */
  SOX_ENCODING_FLAC      , /**< FLAC compression */
  SOX_ENCODING_HCOM      , /**< Mac FSSD files with Huffman compression */
  SOX_ENCODING_WAVPACK   , /**< WavPack with integer samples */
  SOX_ENCODING_WAVPACKF  , /**< WavPack with float samples */
  SOX_ENCODING_ULAW      , /**< u-law signed logs: US telephony, SPARC */
  SOX_ENCODING_ALAW      , /**< A-law signed logs: non-US telephony, Psion */
  SOX_ENCODING_G721      , /**< G.721 4-bit ADPCM */
  SOX_ENCODING_G723      , /**< G.723 3 or 5 bit ADPCM */
  SOX_ENCODING_CL_ADPCM  , /**< Creative Labs 8 --> 2,3,4 bit Compressed PCM */
  SOX_ENCODING_CL_ADPCM16, /**< Creative Labs 16 --> 4 bit Compressed PCM */
  SOX_ENCODING_MS_ADPCM  , /**< Microsoft Compressed PCM */
  SOX_ENCODING_IMA_ADPCM , /**< IMA Compressed PCM */
  SOX_ENCODING_OKI_ADPCM , /**< Dialogic/OKI Compressed PCM */
  SOX_ENCODING_DPCM      , /**< Differential PCM: Fasttracker 2 (xi) */
  SOX_ENCODING_DWVW      , /**< Delta Width Variable Word */
  SOX_ENCODING_DWVWN     , /**< Delta Width Variable Word N-bit */
  SOX_ENCODING_GSM       , /**< GSM 6.10 33byte frame lossy compression */
  SOX_ENCODING_MP3       , /**< MP3 compression */
  SOX_ENCODING_VORBIS    , /**< Vorbis compression */
  SOX_ENCODING_AMR_WB    , /**< AMR-WB compression */
  SOX_ENCODING_AMR_NB    , /**< AMR-NB compression */
  SOX_ENCODING_CVSD      , /**< Continuously Variable Slope Delta modulation */
  SOX_ENCODING_LPC10     , /**< Linear Predictive Coding */
  /* SOX_ENCODING_OPUS      , /\**< Opus compression *\/ */

  SOX_ENCODINGS            /**< End of list marker */
} sox_encoding_t;

/**
Client API:
Flags for sox_encodings_info_t: lossless/lossy1/lossy2.
*/
typedef enum sox_encodings_flags_t {
  sox_encodings_none   = 0, /**< no flags specified (implies lossless encoding) = 0. */
  sox_encodings_lossy1 = 1, /**< encode, decode: lossy once = 1. */
  sox_encodings_lossy2 = 2  /**< encode, decode, encode, decode: lossy twice = 2. */
} sox_encodings_flags_t;


/**
Plugins API:
Is file a real file, a pipe, or a url?
*/
typedef enum lsx_io_type
{
    lsx_io_file, /**< File is a real file = 0. */
    lsx_io_pipe, /**< File is a pipe (no seeking) = 1. */
    lsx_io_url   /**< File is a URL (no seeking) = 2. */
} lsx_io_type;

/*****************************************************************************
Forward declarations:
*****************************************************************************/
typedef struct sox_format_t sox_format_t;
typedef struct sox_effect_t sox_effect_t;
typedef struct sox_effect_handler_t sox_effect_handler_t;
typedef struct sox_format_handler_t sox_format_handler_t;

/*****************************************************************************
Function pointers:
*****************************************************************************/
typedef sox_format_handler_t const * (* sox_format_fn_t)(void);

/**
Client API:
Callback to get information about an effect handler,
used by the table returned from sox_get_effect_fns(void).
@returns Pointer to information about an effect handler.
*/
typedef sox_effect_handler_t const * (*sox_effect_fn_t)(void);

/**
Client API:
Callback to initialize reader (decoder), used by
sox_format_handler.startread.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_format_handler_startread)(
    sox_format_t * ft /**< Format pointer. */
    );

/**
Client API:
Callback to read (decode) a block of samples,
used by sox_format_handler.read.
@returns number of samples read, or 0 if unsuccessful.
*/
typedef size_t (* sox_format_handler_read)(
    sox_format_t * ft, /**< Format pointer. */
    sox_sample_t *buf, /**< Buffer from which to read samples. */
    size_t len /**< Number of samples available in buf. */
    );

/**
Client API:
Callback to close reader (decoder),
used by sox_format_handler.stopread.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_format_handler_stopread)(
    sox_format_t * ft /**< Format pointer. */
    );

/**
Client API:
Callback to initialize writer (encoder),
used by sox_format_handler.startwrite.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_format_handler_startwrite)(
    sox_format_t * ft /**< Format pointer. */
    );

/**
Client API:
Callback to write (encode) a block of samples,
used by sox_format_handler.write.
@returns number of samples written, or 0 if unsuccessful.
*/
typedef size_t (* sox_format_handler_write)(
    sox_format_t * ft, /**< Format pointer. */
    sox_sample_t const * buf, /**< Buffer to which samples are written. */
    size_t len /**< Capacity of buf, measured in samples. */
    );

/**
Client API:
Callback to close writer (decoder),
used by sox_format_handler.stopwrite.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_format_handler_stopwrite)(
    sox_format_t * ft /**< Format pointer. */
    );

/**
Client API:
Callback to reposition reader,
used by sox_format_handler.seek.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_format_handler_seek)(
    sox_format_t * ft, /**< Format pointer. */
    sox_uint64_t offset /**< Sample offset to which reader should be positioned. */
    );

/**
Client API:
Callback to parse command-line arguments (called once per effect),
used by sox_effect_handler.getopts.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_effect_handler_getopts)(
    sox_effect_t * effp, /**< Effect pointer. */
    int argc, /**< Number of arguments in argv. */
    char *argv[] /**< Array of command-line arguments. */
    );

/**
Client API:
Callback to initialize effect (called once per flow),
used by sox_effect_handler.start.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_effect_handler_start)(
    sox_effect_t * effp /**< Effect pointer. */
    );

/**
Client API:
Callback to process samples,
used by sox_effect_handler.flow.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_effect_handler_flow)(
    sox_effect_t * effp, /**< Effect pointer. */
    sox_sample_t const * ibuf, /**< Buffer from which to read samples. */
    sox_sample_t * obuf, /**< Buffer to which samples are written. */
    size_t *isamp, /**< On entry, contains capacity of ibuf; on exit, contains number of samples consumed. */
    size_t *osamp /**< On entry, contains capacity of obuf; on exit, contains number of samples written. */
    );

/**
Client API:
Callback to finish getting output after input is complete,
used by sox_effect_handler.drain.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_effect_handler_drain)(
    sox_effect_t * effp, /**< Effect pointer. */
    sox_sample_t *obuf, /**< Buffer to which samples are written. */
    size_t *osamp /**< On entry, contains capacity of obuf; on exit, contains number of samples written. */
    );

/**
Client API:
Callback to shut down effect (called once per flow),
used by sox_effect_handler.stop.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_effect_handler_stop)(
    sox_effect_t * effp /**< Effect pointer. */
    );

/**
Client API:
Callback to shut down effect (called once per effect),
used by sox_effect_handler.kill.
@returns SOX_SUCCESS if successful.
*/
typedef int (* sox_effect_handler_kill)(
    sox_effect_t * effp /**< Effect pointer. */
    );

/**
Client API:
Callback called while flow is running (called once per buffer),
used by sox_flow_effects.callback.
@returns SOX_SUCCESS to continue, other value to abort flow.
*/
typedef int (* sox_flow_effects_callback)(
    sox_bool all_done,
    void * client_data
    );


/*****************************************************************************
Structures:
*****************************************************************************/
typedef struct sox_globals_t{ ...; } sox_globals_t;

typedef struct sox_signalinfo_t {
  sox_rate_t       rate;         /**< samples per second, 0 if unknown */
  unsigned         channels;     /**< number of sound channels, 0 if unknown */
  unsigned         precision;    /**< bits per sample, 0 if unknown */
  sox_uint64_t     length;       /**< samples * chans in file, 0 if unknown, -1 if unspecified */
  double           * mult;       /**< Effects headroom multiplier; may be null */
} sox_signalinfo_t;

/**
Client API:
Basic information about an encoding.
*/
typedef struct sox_encodings_info_t {
  sox_encodings_flags_t flags; /**< lossy once (lossy1), lossy twice (lossy2), or lossless (none). */
  char const * name;           /**< encoding name. */
  char const * desc;           /**< encoding description. */
} sox_encodings_info_t;

/**
Client API:
Encoding parameters.
*/
typedef struct sox_encodinginfo_t {
  sox_encoding_t encoding; /**< format of sample numbers */
  unsigned bits_per_sample;/**< 0 if unknown or variable; uncompressed value if lossless; compressed value if lossy */
  double compression;      /**< compression factor (where applicable) */

  /**
  Should bytes be reversed? If this is default during sox_open_read or
  sox_open_write, libSoX will set them to either no or yes according to the
  machine or format default.
  */
  sox_option_t reverse_bytes;

  /**
  Should nibbles be reversed? If this is default during sox_open_read or
  sox_open_write, libSoX will set them to either no or yes according to the
  machine or format default.
  */
  sox_option_t reverse_nibbles;

  /**
  Should bits be reversed? If this is default during sox_open_read or
  sox_open_write, libSoX will set them to either no or yes according to the
  machine or format default.
  */
  sox_option_t reverse_bits;

  /**
  If set to true, the format should reverse its default endianness.
  */
  sox_bool opposite_endian;
} sox_encodinginfo_t;

typedef struct sox_oob_t { 
  sox_comments_t comments; 
  ...;
} sox_oob_t;

struct sox_format_t {
  char             * filename;      /**< File name */

  /**
  Signal specifications for reader (decoder) or writer (encoder):
  sample rate, number of channels, precision, length, headroom multiplier.
  Any info specified by the user is here on entry to startread or
  startwrite. Info will be SOX_UNSPEC if the user provided no info.
  At exit from startread, should be completely filled in, using
  either data from the file's headers (if available) or whatever
  the format is guessing/assuming (if header data is not available).
  At exit from startwrite, should be completely filled in, using
  either the data that was specified, or values chosen by the format
  based on the format's defaults or capabilities.
  */
  sox_signalinfo_t signal;

  /* /\** */
  /* Encoding specifications for reader (decoder) or writer (encoder): */
  /* encoding (sample format), bits per sample, compression rate, endianness. */
  /* Should be filled in by startread. Values specified should be used */
  /* by startwrite when it is configuring the encoding parameters. */
  /* *\/ */
  sox_encodinginfo_t encoding;

  char             * filetype;      /**< Type of file, as determined by header inspection or libmagic. */
  sox_oob_t        oob;             /**< comments, instrument info, loop info (out-of-band data) */
  sox_bool         seekable;        /**< Can seek on this file */
  char             mode;            /**< Read or write mode ('r' or 'w') */
  sox_uint64_t     olength;         /**< Samples * chans written to file */
  sox_uint64_t     clips;           /**< Incremented if clipping occurs */
  int              sox_errno;       /**< Failure error code */
  char             sox_errstr[256]; /**< Failure error text */
  void             * fp;            /**< File stream pointer */
  /* lsx_io_type      io_type;         /\**< Stores whether this is a file, pipe or URL *\/ */
  sox_uint64_t     tell_off;        /**< Current offset within file */
  sox_uint64_t     data_start;      /**< Offset at which headers end and sound data begins (set by lsx_check_read_params) */
  sox_format_handler_t handler;     /**< Format handler for this file */
  /* void             * priv;          /\**< Format handler's private data area *\/ */

  ...;
};


/**
Client API:
File buffer info.  Holds info so that data can be read in blocks.
*/
typedef struct sox_fileinfo_t {
  char          *buf;                 /**< Pointer to data buffer */
  size_t        size;                 /**< Size of buffer in bytes */
  size_t        count;                /**< Count read into buffer */
  size_t        pos;                  /**< Position in buffer */
} sox_fileinfo_t;


/**
Client API:
Handler structure defined by each format.
*/
struct sox_format_handler_t {
  unsigned     sox_lib_version_code;  /**< Checked on load; must be 1st in struct*/
  char         const * description;   /**< short description of format */
  char         const * const * names; /**< null-terminated array of filename extensions that are handled by this format */
  unsigned int flags;                 /**< File flags (SOX_FILE_* values). */
  /* sox_format_handler_startread startread; /\**< called to initialize reader (decoder) *\/ */
  /* sox_format_handler_read read;       /\**< called to read (decode) a block of samples *\/ */
  /* sox_format_handler_stopread stopread; /\**< called to close reader (decoder); may be null if no closing necessary *\/ */
  /* sox_format_handler_startwrite startwrite; /\**< called to initialize writer (encoder) *\/ */
  /* sox_format_handler_write write;     /\**< called to write (encode) a block of samples *\/ */
  /* sox_format_handler_stopwrite stopwrite; /\**< called to close writer (decoder); may be null if no closing necessary *\/ */
  /* sox_format_handler_seek seek;       /\**< called to reposition reader; may be null if not supported *\/ */

  /**
  Array of values indicating the encodings and precisions supported for
  writing (encoding). Precisions specified with default precision first.
  Encoding, precision, precision, ..., 0, repeat. End with one more 0.
  Example:
  unsigned const * formats = {
    SOX_ENCODING_SIGN2, 16, 24, 0, // Support SIGN2 at 16 and 24 bits, default to 16 bits.
    SOX_ENCODING_UNSIGNED, 8, 0,   // Support UNSIGNED at 8 bits, default to 8 bits.
    0 // No more supported encodings.
  };
  */
  unsigned     const * write_formats;

  /**
  Array of sample rates (samples per second) supported for writing (encoding).
  NULL if all (or almost all) rates are supported. End with 0.
  */
  sox_rate_t   const * write_rates;

  /**
  SoX will automatically allocate a buffer in which the handler can store data.
  Specify the size of the buffer needed here. Usually this will be sizeof(your_struct).
  The buffer will be allocated and zeroed before the call to startread/startwrite.
  The buffer will be freed after the call to stopread/stopwrite.
  The buffer will be provided via format.priv in each call to the handler.
  */
  size_t       priv_size;

  ...;
};

typedef struct sox_format_tab_t {
  char *name;         /**< Name of format handler */
  sox_format_fn_t fn; /**< Function to call to get format handler's information */
} sox_format_tab_t;

/**
Client API:
Global parameters for effects.
*/
typedef struct sox_effects_globals_t {
  /* sox_plot_t plot;         /\**< To help the user choose effect & options *\/ */
  sox_globals_t * global_info; /**< Pointer to associated SoX globals */
  ...;
} sox_effects_globals_t;

/**
Client API:
Effect handler information.
*/
struct sox_effect_handler_t {
  char const * name;  /**< Effect name */
  char const * usage; /**< Short explanation of parameters accepted by effect */
  unsigned int flags; /**< Combination of SOX_EFF_* flags */
  sox_effect_handler_getopts getopts; /**< Called to parse command-line arguments (called once per effect). */
  sox_effect_handler_start start;     /**< Called to initialize effect (called once per flow). */
  sox_effect_handler_flow flow;       /**< Called to process samples. */
  sox_effect_handler_drain drain;     /**< Called to finish getting output after input is complete. */
  sox_effect_handler_stop stop;       /**< Called to shut down effect (called once per flow). */
  sox_effect_handler_kill kill;       /**< Called to shut down effect (called once per effect). */
  size_t       priv_size;             /**< Size of private data SoX should pre-allocate for effect */
};


/**
Client API:
Effect information.
*/
struct sox_effect_t {
  sox_effects_globals_t    * global_info; /**< global effect parameters */
  sox_signalinfo_t         in_signal;     /**< Information about the incoming data stream */
  sox_signalinfo_t         out_signal;    /**< Information about the outgoing data stream */
  sox_encodinginfo_t       const * in_encoding;  /**< Information about the incoming data encoding */
  sox_encodinginfo_t       const * out_encoding; /**< Information about the outgoing data encoding */
  sox_effect_handler_t     handler;   /**< The handler for this effect */
  sox_uint64_t         clips;         /**< increment if clipping occurs */
  size_t               flows;         /**< 1 if MCHAN, number of chans otherwise */
  size_t               flow;          /**< flow number */
  void                 * priv;        /**< Effect's private data area (each flow has a separate copy) */
  /* The following items are private to the libSoX effects chain functions. */
  sox_sample_t             * obuf;    /**< output buffer */
  size_t                   obeg;      /**< output buffer: start of valid data section */
  size_t                   oend;      /**< output buffer: one past valid data section (oend-obeg is length of current content) */
  size_t               imin;          /**< minimum input buffer content required for calling this effect's flow function; set via lsx_effect_set_imin() */
};

/**
Client API:
Chain of effects to be applied to a stream.
*/
typedef struct sox_effects_chain_t {
  sox_effect_t **effects;                  /**< Table of effects to be applied to a stream */
  size_t length;                           /**< Number of effects to be applied */
  sox_effects_globals_t global_info;       /**< Copy of global effects settings */
  sox_encodinginfo_t const * in_enc;       /**< Input encoding */
  sox_encodinginfo_t const * out_enc;      /**< Output encoding */
  /* The following items are private to the libSoX effects chain functions. */
  size_t table_size;                       /**< Size of effects table (including unused entries) */
  /* sox_sample_t *il_buf;                    /\**< Channel interleave buffer *\/ */
  ...;
} sox_effects_chain_t;

/*****************************************************************************
Functions:
*****************************************************************************/
char const *sox_version(void);

int sox_init(void);

int sox_quit(void);

sox_format_tab_t const *sox_get_format_fns(void);

/**
Client API:
Opens a decoding session for a file. Returned handle must be closed with sox_close().
@returns The handle for the new session, or null on failure.
*/
sox_format_t *
sox_open_read(
    char               const * path,      /**< Path to file to be opened (required). */
    sox_signalinfo_t   const * signal,    /**< Information already known about audio stream, or NULL if none. */
    sox_encodinginfo_t const * encoding,  /**< Information already known about sample encoding, or NULL if none. */
    char             const * filetype   /**< Previously-determined file type, or NULL to auto-detect. */
    );

/**
Client API:
Opens an encoding session for a file. Returned handle must be closed with sox_close().
@returns The new session handle, or null on failure.
*/
sox_format_t *
sox_open_write(
      char               const * path,     /**< Path to file to be written (required). */
      sox_signalinfo_t   const * signal,   /**< Information about desired audio stream (required). */
      sox_encodinginfo_t const * encoding, /**< Information about desired sample encoding, or NULL to use defaults. */
      char               const * filetype, /**< Previously-determined file type, or NULL to auto-detect. */
      sox_oob_t          const * oob,      /**< Out-of-band data to add to file, or NULL if none. */
      sox_bool           (* overwrite_permitted)(char const * filename) /**< Called if file exists to determine whether overwrite is ok. */
    );

/**
Client API:
Reads samples from a decoding session into a sample buffer.
@returns Number of samples decoded, or 0 for EOF.
*/
size_t
sox_read(
    sox_format_t * ft, /**< Format pointer. */
    sox_sample_t *buf, /**< Buffer from which to read samples. */
    size_t len /**< Number of samples available in buf. */
    );

/**
Client API:
Writes samples to an encoding session from a sample buffer.
@returns Number of samples encoded.
*/
size_t
sox_write(
    sox_format_t * ft, /**< Format pointer. */
    sox_sample_t const * buf, /**< Buffer from which to read samples. */
    size_t len /**< Number of samples available in buf. */
    );

/**
Client API:
Closes an encoding or decoding session.
@returns SOX_SUCCESS if successful.
*/
int
sox_close(
    sox_format_t * ft /**< Format pointer. */
    );

/**
Client API:
Sets the location at which next samples will be decoded. Returns SOX_SUCCESS if successful.
@returns SOX_SUCCESS if successful.
*/
int
sox_seek(
    sox_format_t * ft, /**< Format pointer. */
    sox_uint64_t offset, /**< Sample offset at which to position reader. */
    int whence /**< Set to SOX_SEEK_SET. */
    );

/**
Client API:
Finds the effect handler with the given name.
@returns Effect pointer, or null if not found.
*/
sox_effect_handler_t const * sox_find_effect(char const * name /**< Name of effect to find. */);

/**
Client API:
Creates an effect using the given handler.
@returns The new effect, or null if not found.
*/
sox_effect_t *
sox_create_effect(
    sox_effect_handler_t const * eh /**< Handler to use for effect. */
    );

/**
Client API:
Applies the command-line options to the effect.
@returns the number of arguments consumed.
*/
int
sox_effect_options(
    sox_effect_t *effp, /**< Effect pointer on which to set options. */
    int argc, /**< Number of arguments in argv. */
    char * const argv[] /**< Array of command-line options. */
    );

/**
Client API:
Returns an array containing the known effect handlers.
@returns An array containing the known effect handlers.
*/
sox_effect_fn_t const *sox_get_effect_fns(void);


/**
Client API:
Initializes an effects chain. Returned handle must be closed with sox_delete_effects_chain().
@returns Handle, or null on failure.
*/
sox_effects_chain_t *
sox_create_effects_chain(
    sox_encodinginfo_t const * in_enc, /**< Input encoding. */
    sox_encodinginfo_t const * out_enc /**< Output encoding. */
    );

/**
Client API:
Closes an effects chain.
*/
void
sox_delete_effects_chain(
    sox_effects_chain_t *ecp /**< Effects chain pointer. */
    );

/**
Client API:
Adds an effect to the effects chain, returns SOX_SUCCESS if successful.
@returns SOX_SUCCESS if successful.
*/
int
sox_add_effect(
    sox_effects_chain_t * chain, /**< Effects chain to which effect should be added . */
    sox_effect_t * effp, /**< Effect to be added. */
    sox_signalinfo_t * in, /**< Input format. */
       sox_signalinfo_t const * out /**< Output format. */
    );

/**
Client API:
Runs the effects chain, returns SOX_SUCCESS if successful.
@returns SOX_SUCCESS if successful.
*/
int
sox_flow_effects(
    sox_effects_chain_t * chain, /**< Effects chain to run. */
    sox_flow_effects_callback callback, /**< Callback for monitoring flow progress. */
    void * client_data /**< Data to pass into callback. */
    );
