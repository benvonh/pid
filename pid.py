# MIT License
#
# Copyright (c) 2023 Benjamin von Snarski
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
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
