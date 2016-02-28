#ifndef EXAMPLE_H_
#define EXAMPLE_H_
#include <FreeRTOS.h>
#include <stdint.h>
#include <stdbool.h>
#include <system.h>
#include <semphr.h>
/**
 * \defgroup example_driver Example driver 
 * \ingroup HAL
 * \code
 * #include <example.h>
 * \endcode
 * 
 * This is a implementation of a sample driver. This Driver interface has no function and is only for demonstration how to write a new driver 
 * interface and implement a driver. 
 * \{
 */
/**
 * Handle of a Instants of Example
 * 
 * The data of this Handle is private and only the driver has access to the data. 
 */
struct example;
#ifdef CONFIG_EXAMPLE_MULTI
/**
 * Function of a driver in Multi Driver implementation mode 
 */
struct example_ops {
	/**
	 * Init Function
	 * \param index in examples Array
	 * \return Example Instants or NULL
	 */
	struct example *(*example_init)(uint32_t index);
	/**
	 * Deinit Driver Instants 
	 * \param example Instant
	 * \return 0 on ok -1 on failure
	 */
	int32_t (*example_deinit)(struct example *example);
	/**
	 * Sample Function for a driver
	 * \param example Instant
	 * \param params sample param
	 * \return 0 on ok -1 on error
	 */
	int32_t (*example_funcname)(struct example *example, uint32_t params);
};
#endif
/**
 * All driver shall implement this Struct
 * 
 * For Example: 
 * \code{.c}
 * struct example {
 * 	struct example_generic gen;
 * }
 * \endcode
 */
struct example_generic {
	/**
	 * true = is init
	 * false = is not init
	 */
	bool init;
#ifdef CONFIG_EXAMPLE_THREAD_SAVE
	/**
	 * Mutex
	 */
	SemaphoreHandle_t lock;	
#endif
#ifdef CONFIG_EXAMPLE_MULTI
	/**
	 * Ops of driver in Multi mode
	 */
	const struct example_ops *ops;
#endif
};
/**
 * Global container of all example instances
 */
extern struct example **examples;
#ifndef CONFIG_EXAMPLE_MULTI
/**
 * Init Function
 * \param index in examples Array
 * \return Example Instants or NULL
 */
struct example *example_init(uint32_t index);
/**
 * Deinit Driver Instants 
 * \param example Instant
 * \return 0 on ok -1 on failure
 */
int32_t example_deinit(struct example *example);
/**
 * Sample Function for a driver
 * \param example Instant
 * \param params sample param
 * \return 0 on ok -1 on error
 */
int32_t example_funcname(struct example *example, uint32_t params);
#else
/**
 * Init Function
 * \param index in examples Array
 * \return Example Instants or NULL
 */
inline struct example *example_init(uint32_t index) {
	struct example_generic *p = (struct example_generic *) examples[index];
	return p->ops->example_init(index);
}
/**
 * Deinit Driver Instants 
 * \param example Instant
 * \return 0 on ok -1 on failure
 */
inline int32_t example_deinit(struct example *example) {
	struct example_generic *p = (struct example_generic *) example;
	return p->ops->example_deinit(example);
}
/**
 * Sample Function for a driver
 * \param example Instant
 * \param params sample param
 * \return 0 on ok -1 on error
 */
inline int32_t example_funcname(struct example *example, uint32_t params) {
	struct example_generic *p = (struct example_generic *) example;
	return p->ops->example_funcname(example, params);
}
#endif
/**\}*/
#endif
