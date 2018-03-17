package com.nguyenhoang.game;


import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;
import com.google.BasicGameHelpper.*;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class GoogleLeaderboards implements GoogleApiClient.ConnectionCallbacks, GoogleApiClient.OnConnectionFailedListener{
	private static GoogleLeaderboards instance = null;
	private GoogleLeaderboards(){
		waitingLoginGoolePlay = false;
	}
	
	public static GoogleLeaderboards getInstance(){
		if(instance == null){
			instance = new GoogleLeaderboards();
		}
		return instance;
	}
	
	private Activity mActivity;
	private GameHelper gameHelper;
	private boolean waitingLoginGoolePlay;
	
	public void init(Activity activity){
		mActivity = activity;
		gameHelper = new GameHelper(mActivity, GameHelper.CLIENT_GAMES);
		gameHelper.setMaxAutoSignInAttempts(0);
		gameHelper.setup(new GameHelper.GameHelperListener() {			
			@Override
			public void onSignInSucceeded() {
				// TODO Auto-generated method stub
				if(waitingLoginGoolePlay){
					Intent i = Games.Achievements.getAchievementsIntent(gameHelper.getApiClient());
					mActivity.startActivityForResult(i, 1000);
					waitingLoginGoolePlay = false;
				}
			
			}
			
			@Override
			public void onSignInFailed() {
				// TODO Auto-generated method stub
				Log.d("Achiemnet","onSignInFailed");
			}
		});
		gameHelper.beginUserInitiatedSignIn();
	}
	
	public void showAchiment(){
		mActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				if(gameHelper.isSignedIn()){
				//	Log.d("test","show leaderboard");
					Intent i = Games.Achievements.getAchievementsIntent(gameHelper.getApiClient());
					mActivity.startActivityForResult(i, 1000);
				}
				else{
				//	Log.d("test","signin");
					waitingLoginGoolePlay = true;
					gameHelper.beginUserInitiatedSignIn();
					
				}
			}
		});
	}
	
	public void unlock(final int score){
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				if(gameHelper.isSignedIn()){
					if(score == 5){
						Games.Achievements.unlock(gameHelper.getApiClient(), "CgkI3LOvy4EOEAIQAA");
					}
					if(score == 20){
						Games.Achievements.unlock(gameHelper.getApiClient(), "CgkI3LOvy4EOEAIQAQ");
					}
					if(score == 40){
						Games.Achievements.unlock(gameHelper.getApiClient(), "CgkI3LOvy4EOEAIQAg");
					}
					if(score == 80){
						Games.Achievements.unlock(gameHelper.getApiClient(), "CgkI3LOvy4EOEAIQAw");
					}
					if(score == 100){
						Games.Achievements.unlock(gameHelper.getApiClient(), "CgkI3LOvy4EOEAIQBA");
					}
				}								
			}
		});
	}
	
	public static void jniShowAchiment(){
		GoogleLeaderboards.getInstance().showAchiment();
	}
	
	public static void jniUnlock(int score){
		GoogleLeaderboards.getInstance().unlock(score);
	}
	
	public void onStart(){
		gameHelper.onStart(mActivity);
	}
	
	public void onStop(){
		gameHelper.onStop();
	}
	
	public void onActivityResult(final int requestCode, final int resultCode, final Intent data){
		gameHelper.onActivityResult(requestCode, resultCode, data);
	}
	
	@Override
	public void onConnectionFailed(ConnectionResult result) {
		// TODO Auto-generated method stub
		Log.d("google game","onConnectionFailed:"+result.toString());
	}

	@Override
	public void onConnected(Bundle connectionHint) {
		// TODO Auto-generated method stub
		Log.d("google game","onConnected");
	}

	@Override
	public void onConnectionSuspended(int cause) {
		// TODO Auto-generated method stub
		Log.d("google game","onConnectionSuspended");
	}
}
