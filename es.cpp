// #include <functional>

// class Event;
// class EventListener;

// class Event {
//     const std::string name;
// public:
//     Event(const char name[256]) : name(name) {}
//     const std::string& getName() const { return name; }
// };

// class EventListener {
//     std::function<void(Event&)> m_callback;
// public:
//     EventListener(std::function<void(Event&)> callback) : m_callback(callback) {}

//     void operator()(Event& event) { m_callback(event); }
// };

// #include <map>

// class EventStream {
//     std::map<Event, std::vector<EventListener>> listeners;
// public:
//     void subscribe(Event event, EventListener listener) {
//         listeners[event].push_back(listener);
//     }

//     void notify(Event event) {
//         for (auto& listener : listeners[event]) {
//             listener(event);
//         }
//     }
// };

// EventListener listener_getName( [](Event& e) { std::cout << e.getName() << std::endl; } );  // 自定义执行器

// void debug()
// {
//     EventStream stream;

//     Event e("shutdown");    // 任务
//     Event e2("restart");    // 任务
//     stream.subscribe(e, listener_getName);    // 订阅
//     stream.subscribe(e2, listener_getName);   // 订阅

//     stream.notify(e);    // 通知

// }
