package one_way;

//class RWSDKStringResource extends StringResource {
//    private AimSdkWrap aimSdk;
//    String readFunc;
//    String writeFunc;
//    public RWSDKStringResource(String name, boolean bWrite, AimSdkWrap aimSdk, String readFunc, String writeFunc) {
//        super(name, bWrite);
//        this.aimSdk = aimSdk;
//        this.readFunc = readFunc;
//        this.writeFunc = writeFunc;
//    }
//    @Override
//    public String getValue() {
//        String value = null;
//        if (readFunc != null){
//            try {
//                value = (String) aimSdk.getClass().getDeclaredMethod(this.readFunc).invoke(aimSdk, null);
//            } catch (Exception ex) {
//                ;
//            }
//        }
//        return value;
//    }
//    @Override
//    public void setValue(String value) {
//        if (writeFunc != null) {
//            try {
//                aimSdk.getClass().getDeclaredMethod(this.writeFunc, String.class).invoke(aimSdk, value);
//            } catch (Exception ex) {
//                ;
//            }
//        }
//        super.setValue(value);
//    }
//}
//
//public class AimSdkWrap {
//    private static final Logger LOG = LoggerFactory.getLogger(AimSdkWrap.class);
//    private Context mContext;
//    // using framework-level sdk lib
//    private static Advanlib mAdvanLib;
//    // using app-level sdk lib
//    //private static AppSdkLib mAdvanLib;
//
//    public AimSdkWrap(Context context) {
//        LOG.info("Initial Advanlib");
//        mContext = context;
//        mAdvanLib = new Advanlib(context);
//        //mAdvanLib = new AppSdkLib(context);
//    }
//
//    // invode from AdvanLib
//    public boolean isWifiEnabled() {
//        boolean bRet = false;
//        bRet = mAdvanLib.isWifiEnabled();
//        LOG.info("isWifiEnabled: ret=" + bRet);
//        return bRet;
//    }
//
//    public void enableWifi(boolean enable) {
//        LOG.info("enableWifi: " + enable);
//        mAdvanLib.enableWifi(enable);
//    }
//
//    public boolean isBluetoothEnabled() {
//        boolean bRet = false;
//        bRet = mAdvanLib.isBluetoothEnabled();
//        LOG.info("isBluetoothEnabled: ret=" + bRet);
//        return bRet;
//    }
//}
