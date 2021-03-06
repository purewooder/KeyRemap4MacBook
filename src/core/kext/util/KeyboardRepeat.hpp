#ifndef KEYBOARDREPEAT_HPP
#define KEYBOARDREPEAT_HPP

#include "base.hpp"
#include "CallbackWrapper.hpp"
#include "Config.hpp"
#include "KeyCode.hpp"
#include "List.hpp"
#include "ParamsUnion.hpp"
#include "TimerWrapper.hpp"

namespace org_pqrs_KeyRemap4MacBook {
  class KeyboardRepeat {
  public:
    enum {
      // getID() will return [0 .. MAX_KEYBOARDREPEATID] (including edge).
      MAX_KEYBOARDREPEATID = 10000,
    };
    KeyboardRepeat(void) {}

    static void initialize(IOWorkLoop& workloop);
    static void terminate(void);

    static void cancel(void);

    static int getID(void) { return id_; }

    // --------------------------------------------------
    static void set(EventType eventType,
                    Flags flags,
                    KeyCode key,
                    KeyboardType keyboardType,
                    int wait);

    static void set(const Params_KeyboardEventCallBack& p,
                    int wait = Config::get_repeat_initial_wait()) {
      set(p.eventType, p.flags, p.key, p.keyboardType, wait);
    }

    // for consumer
    static void set(EventType eventType,
                    Flags flags,
                    ConsumerKeyCode key);
    static void set(const Params_KeyboardSpecialEventCallback& p) {
      set(p.eventType, p.flags, p.key);
    }

    // --------------------------------------------------
    // primitive operations.
    static void primitive_add_downup(Flags flags,
                                     KeyCode key,
                                     KeyboardType keyboardType);

    static void primitive_add(EventType eventType,
                              Flags flags,
                              ConsumerKeyCode key);

    static int primitive_start(int wait = Config::get_repeat_initial_wait());

  private:
    class Item : public List::Item {
    public:
      enum Type {
        TYPE_NORMAL,
        TYPE_DOWNUP,
      };

      Item(const Params_KeyboardEventCallBack& p, Type t)        : params(p), type(t) {}
      Item(const Params_KeyboardSpecialEventCallback& p, Type t) : params(p), type(t) {}
      virtual ~Item(void) {}

      ParamsUnion params;
      Type type;
    };

    // ------------------------------------------------------------
    static void fire_timer_callback(OSObject* owner, IOTimerEventSource* sender);

    static void primitive_add(EventType eventType,
                              Flags flags,
                              KeyCode key,
                              KeyboardType keyboardType,
                              Item::Type type);

    static int succID(void) {
      ++id_;
      if (id_ > MAX_KEYBOARDREPEATID) id_ = 0;
      return id_;
    }

    static List* queue_;
    static TimerWrapper fire_timer_;
    static int id_;
  };
}

#endif
