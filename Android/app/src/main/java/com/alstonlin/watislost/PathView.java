package com.alstonlin.watislost;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Environment;
import android.util.AttributeSet;
import android.view.View;

/**
 * Created by Alston on 11/15/2015.
 */
public class PathView extends View {

    private double[][] path;

    public PathView(Context context, AttributeSet as) {
        super(context, as);
    }

    public void setPath(double[][] path){
        this.path = path;
        invalidate();
    }

    public void onDraw(Canvas canvas){
        if (path != null) {
            super.onDraw(canvas);
            //TODO: Make this not hardcoded
            int height = getHeight();
            int width = getWidth();
            Paint p = new Paint();
            Bitmap b = BitmapFactory.decodeResource(getResources(), R.drawable.map);
            p.setColor(Color.GREEN);
            p.setStrokeWidth(10);
            canvas.drawBitmap(b, 0, 0, p);

            for (int i = 1; i < path.length; i++) {
                double drawXPrev = width * path[i - 1][1];
                double drawYPrev = height * path[i - 1][0] + 100;
                double drawY = height * path[i][0] + 100;
                double drawX = width * path[i][1];
                canvas.drawLine((int) drawXPrev, (int) drawYPrev, (int) drawX, (int) drawY, p);
            }
        }
    }


}
