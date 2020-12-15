#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

template <typename Clock = boost::posix_time::microsec_clock>
class BasicPtimer
{
public:
    BasicPtimer()
    {
        restart();
    }

    void restart()
    {
        m_startTime = Clock::local_time();
    }

    void elapsed() const
    {
        std::cout << Clock::local_time() - m_startTime << std::endl;
    }

    ~BasicPtimer()
    {
        elapsed();
    }

private:
    boost::posix_time::ptime m_startTime;
};

int main(int argc, char *argv[])
{
    typedef BasicPtimer<boost::posix_time::microsec_clock> mptimer; // 最小的计时单位1us
    typedef BasicPtimer<boost::posix_time::second_clock> sptimer;   // 最小的计时单位s

    {
        mptimer t;
    }
}
