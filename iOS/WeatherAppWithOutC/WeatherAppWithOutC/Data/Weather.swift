import Foundation

struct Weather {
    private var _temperature: String
    private var _weekDay: String
    private var _loadData: Bool
    private var _date: String
    private var _prognosImage: String

    init(temperature: String, weekDay: String, loadData: Bool, date: String, prognosImage: String) {
        self._temperature = temperature
        self._weekDay = weekDay
        self._loadData = loadData
        self._date = date
        self._prognosImage = prognosImage
    }

    var temperature: String {
        get {
            return _temperature
        }
        set {
            _temperature = newValue
        }
    }

    var weekDay: String {
        get {
            return _weekDay
        }
        set {
            _weekDay = newValue
        }
    }

    var loadData: Bool {
        get {
            return _loadData
        }
        set {
            _loadData = newValue
        }
    }

    var date: String {
        get {
            return _date
        }
        set {
            _date = newValue
        }
    }

    var prognosImage: String {
        get {
            return _prognosImage
        }
        set {
            _prognosImage = newValue
        }
    }
}
