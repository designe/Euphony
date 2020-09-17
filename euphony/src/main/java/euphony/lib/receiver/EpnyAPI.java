package euphony.lib.receiver;

public class EpnyAPI {
    private int mId;
    private int mFreqIndex;
    APICallDetector mAPICallback;

    public EpnyAPI(int id, APICallDetector callback) {
        mId = id;
        mAPICallback = callback;
    }

    public int getId() {
        return mId;
    }

    public void setFreqIndex(int idx) {
        mFreqIndex = idx;
    }

    public int getFreqIndex() {
        return mFreqIndex;
    }

    public APICallDetector getCallback() {
        return mAPICallback;
    }

}