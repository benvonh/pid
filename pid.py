class Base(object):
    def __init__(self) -> None:
        self.dt = 0.0

    def __call__(self, err: float) -> float:
        raise NotImplementedError

class P(Base):
    def __init__(self) -> None:
        super().__init__()
        self.Kp = 0.0

    def __call__(self, err: float) -> float:
        return self.Kp * err

class I(Base):
    def __init__(self) -> None:
        super().__init__()
        self.Ki = 0.0
        self._sum = 0.0

    def __call__(self, err: float) -> float:
        self._sum += err * self.dt
        return self.Ki * self._sum

    def get_total_error(self) -> float:
        return self._sum

class D(Base):
    def __init__(self) -> None:
        super().__init__()
        self.Kd = 0.0
        self._prev = 0.0

    def __call__(self, err: float) -> float:
        out = (err - self._prev) / self.dt
        self._prev = err
        return self.Kd * out

    def get_prev_error(self) -> float:
        return self._prev

class PI(P, I):
    def __init__(self) -> None:
        P.__init__(self)
        I.__init__(self)

    def __call__(self, err: float) -> float:
        p = P.__call__(self, err)
        i = I.__call__(self, err)
        return p + i

class PD(P, D):
    def __init__(self) -> None:
        P.__init__(self)
        D.__init__(self)

    def __call__(self, err: float) -> float:
        p = P.__call__(self, err)
        d = D.__call__(self, err)
        return p + d

class PID(P, I, D):
    def __init__(self) -> None:
        P.__init__(self)
        I.__init__(self)
        D.__init__(self)

    def __call__(self, err: float) -> float:
        p = P.__call__(self, err)
        i = I.__call__(self, err)
        d = D.__call__(self, err)
        return p + i + d
