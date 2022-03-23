/**
 * @file
 *  The CI Lab App header file containing version information
 */
#ifndef CI_LAB_VERSION_H
#define CI_LAB_VERSION_H

/* Development Build Macro Definitions */

#define CI_LAB_BUILD_NUMBER 10 /*!< Development Build: Number of commits since baseline */
#define CI_LAB_BUILD_BASELINE \
    "v2.5.0-rc4" /*!< Development Build: git tag that is the base for the current development */

/* Version Macro Definitions */

#define CI_LAB_MAJOR_VERSION 2 /*!< @brief ONLY APPLY for OFFICIAL releases. Major version number. */
#define CI_LAB_MINOR_VERSION 3 /*!< @brief ONLY APPLY for OFFICIAL releases. Minor version number. */
#define CI_LAB_REVISION      0 /*!< @brief ONLY APPLY for OFFICIAL releases. Revision version number. */

/*!
 * @brief Mission revision.
 *
 * Set to 0 on OFFICIAL releases, and set to 255 (0xFF) on development versions.
 * Values 1-254 are reserved for mission use to denote patches/customizations as needed.
 */
#define CI_LAB_MISSION_REV 0xFF

#define CI_LAB_STR_HELPER(x) #x /*!< @brief Helper function to concatenate strings from integer macros */
#define CI_LAB_STR(x)        CI_LAB_STR_HELPER(x) /*!< @brief Helper function to concatenate strings from integer macros */

/*! @brief Development Build Version Number.
 * @details Baseline git tag + Number of commits since baseline. @n
 * See @ref cfsversions for format differences between development and release versions.
 */
#define CI_LAB_VERSION CI_LAB_BUILD_BASELINE "+dev" CI_LAB_STR(CI_LAB_BUILD_NUMBER)

/*! @brief Development Build Version String.
 * @details Reports the current development build's baseline, number, and name. Also includes a note about the latest
 * official version. @n See @ref cfsversions for format differences between development and release versions.
 */
#define CI_LAB_VERSION_STRING                       \
    " CI Lab App DEVELOPMENT BUILD " CI_LAB_VERSION \
    ", Last Official Release: v2.3.0" /* For full support please use this version */

#endif
