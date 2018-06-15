class DotProduct {
    private Double[] x;
    private Double[] y;
    private double z;

    public Double[] getX(){
        return x;
    }
    public Double[] getY(){
        return y;
    }
    public double getZ(){
        return z;
    }

    public void setX(Double[] x){
        this.x = x;
    }
    public void setY(Double[] y){
        this.y = y;
    }
    public void setZ(double z){
        this.z = z;
    }

    public native double CalculateDotProduct1(Double[] a, Double[] b);

    public native double CalculateDotProduct2(Double[] a);

    public native void CalculateDotProduct3();

    private void CalculateInnerDotProduct(){
        z = CalculateDotProduct1(x,y);
    }


    public static void main(String... args){
        System.loadLibrary("DotProductDLL");

        Double x[] = {15d, 5d, 8d, -7d};
        Double y[] = {8d, 5d, -4d, 2d};

        DotProduct dotP = new DotProduct();

        System.out.println( dotP.CalculateDotProduct1(x,y) );
        dotP.setY(y);
        System.out.println( dotP.CalculateDotProduct2(x) );
        dotP.CalculateDotProduct3();
        System.out.println( dotP.getZ() );
    }
}
