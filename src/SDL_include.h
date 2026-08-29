#ifndef SDL_INCLUDE_H
#ifndef SDL_INCLUDE_H_GUARD
#define SDL_INCLUDE_H_GUARD

/************************************************
 *                  SDL.h                       *
 *************************************************/
#ifdef INCLUDE_SDL
#ifdef _WIN32
#include <SDL2/SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>

#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL
#endif  // INCLUDE_SDL

/************************************************
 *               SDL_image.h                    *
 *************************************************/
#ifdef INCLUDE_SDL_IMAGE
#ifdef _WIN32
#include <SDL2/SDL_image.h>
#elif __APPLE__
#include <SDL2/SDL_image.h>

#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL_image.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL_IMAGE
#endif  // INCLUDE_SDL_IMAGE

/************************************************
 *               SDL_mixer.h                    *
 *************************************************/
#ifdef INCLUDE_SDL_MIXER
#ifdef _WIN32
#include <SDL2/SDL_mixer.h>
#elif __APPLE__
#include <SDL2/SDL_mixer.h>

#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL_mixer.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL_MIXER
#endif  // INCLUDE_SDL_MIXER

/************************************************
 *                SDL_ttf.h                     *
 *************************************************/
#ifdef INCLUDE_SDL_TTF
#ifdef _WIN32
#include <SDL2/SDL_ttf.h>
#elif __APPLE__
#include <SDL2/SDL_ttf.h>

#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL_ttf.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL_TTF
#endif  // INCLUDE_SDL_TTF

/************************************************
 *                SDL_net.h                     *
 *************************************************/
#ifdef INCLUDE_SDL_NET
#ifdef _WIN32
#include <SDL2/SDL_net.h>
#elif __APPLE__
#include <SDL2/SDL_net.h>

#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL_net.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL_NET
#endif  // INCLUDE_SDL_NET

#endif  // SDL_INCLUDE_H_GUARD
#endif