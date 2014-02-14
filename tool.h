#ifndef _TOOL_H_
#define _TOOL_H_

#include <string>
#include <istream>
#include "dice.h"

// Tool_target is a list of ways that tools can select their target
enum Tool_target
{
  TOOL_TARGET_NULL = 0, // Default - doesn't use a target
  TOOL_TARGET_ADJACENT, // "adjacent" - press a direction key, apply there
  TOOL_TARGET_RANGED,   // "ranged" - target any square
  TOOL_TARGET_MAX
};

Tool_target lookup_tool_target(std::string name);
std::string tool_target_name(Tool_target target);

enum Tool_special_type
{
  TOOL_SPECIAL_NULL = 0,  // Default - don't do anything
  TOOL_SPECIAL_EXPLOSION, // Make an explosion
  TOOL_SPECIAL_LIGHT,     // Provide some light
  TOOL_SPECIAL_MAX
};

struct Tool_special
{
  virtual ~Tool_special(){}

  virtual Tool_special_type get_type() { return TOOL_SPECIAL_NULL; }

  virtual bool load_data(std::istream& data, std::string owner_name)
  {
    return false;
  }

  virtual bool effect() { return false; }
};

struct Tool_special_explosion : public Tool_special
{
  Tool_special_explosion();
  virtual ~Tool_special_explosion(){}

  virtual Tool_special_type get_type() { return TOOL_SPECIAL_EXPLOSION; }

  virtual bool load_data(std::istream& data, std::string owner_name);
  virtual bool effect() { return false; }; // TODO: This

  Dice damage;
  Dice radius;
// TODO: Field output, shrapnel, shrapnel damage, other effects (flashbang), etc
};

struct Tool_special_light : public Tool_special
{
  Tool_special_light();
  virtual ~Tool_special_light(){}

  virtual Tool_special_type get_type() { return TOOL_SPECIAL_LIGHT; }

  virtual bool load_data(std::istream& data, std::string owner_name);
  virtual bool effect() { return false; }  // TODO: This

  int light;
};

struct Tool_action
{
  Tool_action();
  ~Tool_action();

  std::string signal;     // Signal sent to terrain/items/monsters
  Tool_special *special;  // Hardcoded action
  Tool_target target;     // The target it's sent to
  int ap_cost;            // Action Points used
  int charge_cost;        // Charges used

  bool load_data(std::istream& data, std::string owner_name = "Unknown");
};
  
#endif
